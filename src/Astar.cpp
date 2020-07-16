//
// Created by vivedo on 15/05/20.
//

#include "Astar.hpp"

Astar::Astar(std::forward_list<sf::IntRect> &obstacles, Vector2u8 mapSize) : obstacles(obstacles), mapSize(mapSize) {}

Path *Astar::getPath(Vector2u8 a, Vector2u8 b) {
    return getPath(new Node({nullptr, a.x, a.y}), new Node({nullptr, b.x, b.y}));
}

bool Astar::isValid(uint16_t x, uint16_t y) const {
    return (x >= 0) && (y >= 0) && (x < mapSize.x) && (y < mapSize.y);
}

bool Astar::isBlocked(uint8_t x, uint8_t y) {
    for (sf::IntRect obstacle : obstacles)
        if (obstacle.contains(x, y))
            return true;
    return false;
}

Path *Astar::getPath(Node *from, Node *to) {
    from->g = 0;
    from->f = h((*from), (*to));

    openList.push_front(from);

    while (!openList.empty()) {

        Node *currentNode = openList.front();
        for (Node *node : openList) {
            if (node->f < currentNode->f)
                currentNode = node;
        }

        /*
         * Pathfinding done, return path
         */
        if (*currentNode == *to) {
            auto path = new Path;

            for (Node *pathNode = currentNode; pathNode != nullptr; pathNode = pathNode->parent)
                path->push_front({pathNode->x, pathNode->y});

            clearLists();

            return path;
        }

        openList.remove(currentNode);
        closedList.push_front(currentNode);

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
                if (!isValid(currentNode->x + x, currentNode->y + y))
                    continue;

                /*
                 * Ignore nodes between blocked boundaries
                 */
                if (isBlocked(currentNode->x + x, currentNode->y + y))
                    continue;

                /*
                 * Pointer to current neighbor node, will be retrieved from one of the lists if exists or created if not
                 */
                Node *neighbor = nullptr;

                /*
                 * Uses (x * y) to determine diagolal children as with coordinates from -1 to 1
                 * all elements in center row or center column multiply by x=0 or y=0
                 */
                uint16_t g = currentNode->g + ((x * y) ? DIAGONAL_COST : NORMAL_COST);

                auto &&closedNeighbor = std::find_if(closedList.begin(), closedList.end(),
                                                     [x, y, &currentNode](const Node *other) {
                                                          return currentNode->x + x == other->x &&
                                                                 currentNode->y + y == other->y;
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
                                                   [x, y, &currentNode](const Node *other) {
                                                        return currentNode->x + x == other->x &&
                                                               currentNode->y + y == other->y;
                                                    });

                /*
                 * If neighbor didnt't exist in closedList but does in openList store it, otherwise create a new node
                 */
                if (openNeighbor != openList.end() && neighbor == nullptr)
                    neighbor = *openNeighbor;
                else
                    neighbor = new Node({currentNode, static_cast<uint8_t>(currentNode->x + x),
                                         static_cast<uint8_t>(currentNode->y + y), g});

                /*
                 * A* handling
                 */
                if (openNeighbor == openList.end() || g < neighbor->g) {;

                    neighbor->parent = currentNode;
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

void Astar::clearLists() {
    for(Node *n : openList) {
        delete n;
        n = nullptr;
    }

    for(Node *n : closedList) {
        delete n;
        n = nullptr;
    }

    openList.clear();
    closedList.clear();
}
