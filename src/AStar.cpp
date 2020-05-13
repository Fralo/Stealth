//
// Created by mattia on 10/05/20.
//

#include "AStar.hpp"

std::vector <Node> AStar::getPath(Node hunter, Node dest) {
    std::vector <Node> empty;
    if (!isValid(dest.x, dest.y)) {
        //Destination is an obstacle;
        return empty;
    }
    if (isDestination(hunter.x, hunter.y, dest)) {
        //You are the destination
        return empty;
    }
    bool closedList[mapSize.x-1][mapSize.y-1];
    //Get the overview of the map
    Node allMap[mapSize.x-1][mapSize.y-1];
    for (int x = 1; x < (mapSize.x-1); x++) {
        for (int y = 1; y < (mapSize.y-1); y++) {
            allMap[x][y].fCost = FLT_MAX;
            allMap[x][y].gCost = FLT_MAX;
            allMap[x][y].hCost = FLT_MAX;
            allMap[x][y].parentX = -1;
            allMap[x][y].parentY = -1;
            allMap[x][y].x = x;
            allMap[x][y].y = y;

            closedList[x][y] = false;
        }
    }

    //Initialize our starting list
    int x = hunter.x/mapSize.x;
    int y = hunter.y/mapSize.y;
    allMap[x][y].fCost = 0.0;
    allMap[x][y].gCost = 0.0;
    allMap[x][y].hCost = 0.0;
    allMap[x][y].parentX = x;
    allMap[x][y].parentY = y;

    std::vector <Node> openList;
    openList.emplace_back(allMap[x][y]);
    bool destinationFound = false;

    while (!openList.empty() && openList.size() < (mapSize.x-1) * (mapSize.y-1)) {
        Node node;
        do {
            float temp = FLT_MAX;
            std::vector<Node>::iterator itNode;
            for (std::vector<Node>::iterator it = openList.begin(); it != openList.end(); it = next(it)) {
                Node n = *it;
                if (n.fCost < temp) {
                    temp = n.fCost;
                    itNode = it;
                }
            }
            if (openList.empty()) {
                //Not existing path
                return empty;
            }
            node = *itNode;
            openList.erase(itNode);
        } while (!isValid(node.x, node.y));

        x = node.x/mapSize.x;
        y = node.y/mapSize.y;
        closedList[x][y] = true;

        //For each neighbour starting from North-West to South-East
        for (int newX = -1; newX <= 1; newX++) {
            for (int newY = -1; newY <= 1; newY++) {
                double gNew, hNew, fNew;
                //trying to deny diagonals
                if ((abs(newX) != abs(newY)) && isValid(x + newX, y + newY)) {
                    if (isDestination(x + newX, y + newY, dest)) {
                        //Destination found - make path
                        allMap[x + newX][y + newY].parentX = x;
                        allMap[x + newX][y + newY].parentY = y;
                        destinationFound = true;
                        return makePath(*allMap, dest);
                    } else if (!closedList[x + newX][y + newY]) {
                        gNew = node.gCost + 1.0;
                        hNew = calculateH(x + newX, y + newY, dest);
                        fNew = gNew + hNew;
                        // Check if this path is better than the one already present
                        if (allMap[x + newX][y + newY].fCost == FLT_MAX ||
                            allMap[x + newX][y + newY].fCost > fNew) {
                            // Update the details of this neighbour node
                            allMap[x + newX][y + newY].fCost = fNew;
                            allMap[x + newX][y + newY].gCost = gNew;
                            allMap[x + newX][y + newY].hCost = hNew;
                            allMap[x + newX][y + newY].parentX = x;
                            allMap[x + newX][y + newY].parentY = y;
                            openList.emplace_back(allMap[x + newX][y + newY]);
                        }
                    }
                }
            }
        }
    }
    if (!destinationFound) {
        //Destination not found;
        return empty;
    }
}

std::vector <Node> AStar::makePath(Node *map, Node dest) {
    try {
        int x = dest.x;
        int y = dest.y;
        std::stack <Node> path;
        std::vector <Node> usablePath;

        while (!(map[x * mapSize.y - 1 + y].parentX == x && map[x * mapSize.y - 1 + y].parentY == y)
               && map[x * mapSize.y - 1 + y].x != -1 && map[x * mapSize.y - 1 + y].y != -1) {
            path.push(map[x * mapSize.y - 1 + y]);
            int tempX = map[x * mapSize.y - 1 + y].parentX;
            int tempY = map[x * mapSize.y - 1 + y].parentY;
            x = tempX;
            y = tempY;

        }
        path.push(map[x * mapSize.y - 1 + y]);

        while (!path.empty()) {
            Node top = path.top();
            path.pop();
            usablePath.emplace_back(top);
        }
        return usablePath;
    }
    catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

double AStar::calculateH(int x, int y, Node dest) {

    double H = (sqrt((x - dest.x) * (x - dest.x) + (y - dest.y) * (y - dest.y)));

    return H;
}

bool AStar::isDestination(int x, int y, Node dest) {
    return x == dest.x && y == dest.y;
}

bool AStar::isValid(int x, int y) {

    for (auto it = obstacles->begin(); it != obstacles->end(); ++it) {
        if (x < (it->left + it->width) && x > it->left && y < it->top && y > (it->top - it->height))
            return false;
    }
    return true;
}

AStar::AStar(std::forward_list <Obstacle> &obs, sf::Vector2<unsigned int> mSize) : obstacles(&obs), mapSize(
        mSize) {

}



