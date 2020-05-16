//
// Created by vivedo on 15/05/20.
//

#include "AStar2.hpp"

AStar2::AStar2(std::forward_list<sf::IntRect> &obstacles, sf::Vector2u mapSize) : obstacles(obstacles), mapSize(mapSize) {}

std::forward_list<sf::Vector2<uint8>> *AStar2::getPath(sf::Vector2<uint8> a, sf::Vector2<uint8> b) {
    return getPath(new Node2({nullptr, a.x, a.y}), new Node2({nullptr, b.x, b.y}));
}

bool AStar2::isValid(uint16 x, uint16 y) const {
    return (x >= 0) && (y >= 0) && (x < mapSize.x) && (y < mapSize.y);
}

bool AStar2::isBlocked(uint8 x, uint8 y) {
    for (sf::IntRect obstacle : obstacles)
        if (obstacle.contains(x, y))
            return true;
    return false;
}

std::forward_list<sf::Vector2<uint8>> *AStar2::getPath(Node2 *from, Node2 *to) {
    from->g = 0;
    from->f = h((*from), (*to));

    openList.push_front(from);

    while (!openList.empty()) {

        Node2 *currentNode2 = openList.front();
        for (Node2 *node : openList) {
            if (node->f < currentNode2->f)
                currentNode2 = node;
        }

        /*
         * Pathfinding done, return path
         */
        if (*currentNode2 == *to) {
            auto path = new std::forward_list<sf::Vector2<uint8>>;

            for (Node2 *pathNode2 = currentNode2; pathNode2 != nullptr; pathNode2 = pathNode2->parent)
                path->push_front({pathNode2->x, pathNode2->y});

            clearLists();

            return path;
        }

        openList.remove(currentNode2);
        closedList.push_front(currentNode2);

        for (char x = -1; x <= 1; x++)
            for (char y = -1; y <= 1; y++) {
                /*
                 * Ignore current node
                 */
                if (!x && !y)
                    continue;

                /*
                 * Ignore nodes outside map limits
                 */
                if (!isValid(currentNode2->x + x, currentNode2->y + y))
                    continue;

                /*
                 * Ignore nodes between blocked boundaries
                 */
                if (isBlocked(currentNode2->x + x, currentNode2->y + y))
                    continue;

                /*
                 * Pointer to current neighbor node, will be retrieved from one of the lists if exists or created if not
                 */
                Node2 *neighbor = nullptr;

                /*
                 * Uses (x * y) to determine diagolal children as with coordinates from -1 to 1
                 * all elements in center row or center column multiply by x=0 or y=0
                 */
                uint16 g = currentNode2->g + ((x * y) ? DIAGONAL_COST : NORMAL_COST);

                auto &&closedNeighbor = std::find_if(closedList.begin(), closedList.end(),
                                                     [x, y, &currentNode2](const Node2 *other) {
                                                          return currentNode2->x + x == other->x &&
                                                                 currentNode2->y + y == other->y;
                                                      });


                /*
                 * ignores neighbor in closedList if worse than current one
                 */
                if (closedNeighbor != closedList.end()) {
                    if (g >= (*closedNeighbor)->g)
                        continue;

                    /*
                     * If neighbor exists in closedList store it
                     */
                    neighbor = *closedNeighbor;
                }

                /*
                 * if (x,y) is in openList and neighbor is less than the one in the list updates list's neighbor with neighbor
                 * parameters, otherwise add neighbor to openList
                 */
                auto &&openNeighbor = std::find_if(openList.begin(), openList.end(),
                                                   [x, y, &currentNode2](const Node2 *other) {
                                                        return currentNode2->x + x == other->x &&
                                                               currentNode2->y + y == other->y;
                                                    });

                /*
                 * If neighbor didnt't exist in closedList but does in openList store it, otherwise create a new node
                 */
                if (openNeighbor != openList.end() && neighbor == nullptr)
                    neighbor = *openNeighbor;
                else
                    neighbor = new Node2({currentNode2, static_cast<uint8>(currentNode2->x + x),
                                         static_cast<uint8>(currentNode2->y + y), g});

                /*
                 * A* handling
                 */
                if (openNeighbor == openList.end() || g < neighbor->g) {;

                    neighbor->parent = currentNode2;
                    neighbor->g = g;
                    neighbor->f = g + h((*neighbor), (*to));

                    if(openNeighbor == openList.end())
                        openList.push_front(neighbor);
                }
            }
    }

    clearLists();
    return nullptr;
}

void AStar2::clearLists() {
    for(Node2 *n : openList) {
        delete n;
        n = nullptr;
    }

    for(Node2 *n : closedList) {
        delete n;
        n = nullptr;
    }

    openList.clear();
    closedList.clear();
}
