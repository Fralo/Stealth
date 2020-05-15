//
// Created by vivedo on 15/05/20.
//

#include "AStar2.hpp"

AStar2::AStar2(std::list<sf::IntRect> &obstacles, sf::Vector2u mapSize) : obstacles(obstacles), mapSize(mapSize) {}

std::list<sf::Vector2<uint8>> * AStar2::getPath(sf::Vector2<uint8> a, sf::Vector2<uint8> b) {
    return getPath({nullptr, a.x, a.y, 0}, {nullptr, b.x, b.y});
}

bool AStar2::isValid(uint16 x, uint16 y) const {
    return (x >= 0) && (y >= 0) && (x < mapSize.x) && (y < mapSize.y);
}

bool AStar2::isBlocked(uint8 x, uint8 y) {
    for(sf::IntRect obstacle : obstacles)
        if(obstacle.contains(x, y))
            return true;
    return false;
}

std::list<sf::Vector2<uint8>> * AStar2::getPath(Node from, Node to) {
    from.g = 0;
    from.f = h(from, to);

    openList.push_back(from);

    while(!openList.empty()) {

        Node &currentNode = openList.front();
        for(Node &node : openList) {
            if(node < currentNode)
                currentNode = node;
        }

        /*
         * Pathfinding done, return path
         */
        if(currentNode == to) {
            auto path = new std::list<sf::Vector2<uint8>>;

            for(Node *pathNode = &currentNode; pathNode != nullptr; pathNode = pathNode->parent)
                path->push_front({pathNode->x, pathNode->y});

            return path;
        }

        openList.remove(currentNode);
        closedList.push_front(currentNode);

        for(char x = -1; x <= 1; x++)
            for(char y = -1; y <= 1; y++) {
                // ignore currentNode
                if(!x && !y)
                    continue;

                // ignore neighbor if out of map
                if(!isValid(currentNode.x + x, currentNode.y + y))
                    continue;

                // obstacles
                if(isBlocked(currentNode.x + x, currentNode.y + y))
                    continue;

                Node neighbor = {&currentNode, static_cast<uint8>(currentNode.x + x), static_cast<uint8>(currentNode.y + y)};

                // if neighbor in closed list ignore
                auto&& closedNeighbour = std::find(closedList.begin(), closedList.end(), neighbor);
                if(closedNeighbour != closedList.end())
                    continue;
/*
                 * Uses (x * y) to determine diagolal children as with coordinates from -1 to 1
                 * all elements in center row or center column multiply by x=0 or y=0
                 */
                neighbor.g = currentNode.g + ((x * y) ? DIAGONAL_COST : NORMAL_COST);
                neighbor.f = neighbor.g + h(neighbor, to);

                /*
                 * if (x,y) is in openList and neighbor is less than the one in the list updates list's neighbor with neighbor
                 * parameters, otherwise add neighbor to openList
                 */
                auto&& listChild = std::find(openList.begin(), openList.end(), neighbor);
                if (listChild == openList.end())
                    openList.push_back(neighbor);
                else // neighbor in openList
                    if (neighbor < *listChild) {
                        listChild->g = neighbor.g;
                        listChild->parent = neighbor.parent;
                    }
            }


    }

    return nullptr;
}
