//
// Created by mattia on 10/05/20.
//

#include "AStar.hpp"




AStar::AStar(std::forward_list <Obstacle*> &obs, sf::Vector2u mSize, sf::Vector2u tSize) : obstacles(obs), mapSize(mSize), tileSize(tSize) {}

std::vector <Node> AStar::getPath(Node hunter, Node dest) {std::vector<Node> empty;
    hunter.x = hunter.x/tileSize.x;
    hunter.y = hunter.y/tileSize.y;
    dest.x = dest.x/tileSize.x;
    dest.y = dest.y/tileSize.y;
    if (!isValid(dest.x, dest.y)) {
        //Destination is an obstacle;
        return empty;
    }
    if (isDestination(hunter.x, hunter.y, dest)) {
        //You are the destination
        return empty;
    }
    bool closedList[mapSize.x][mapSize.y];
    //Get the overview of the map
    Node allMap[mapSize.x][mapSize.y];
    for (int x = 0; x < (mapSize.x); x++) {
        for (int y = 0; y < (mapSize.y); y++) {
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
    int x = hunter.x;
    int y = hunter.y;
    allMap[x][y].fCost = 0.0;
    allMap[x][y].gCost = 0.0;
    allMap[x][y].hCost = 0.0;
    allMap[x][y].parentX = x;
    allMap[x][y].parentY = y;

    std::vector<Node> openList;
    openList.emplace_back(allMap[x][y]);
    bool destinationFound = false;

    while (!openList.empty()&&openList.size()<(mapSize.x)*(mapSize.y)) {
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
            if(openList.empty()) {
                //Not existing path
                return empty;
            }
            node = *itNode;
            openList.erase(itNode);
        } while (!isValid(node.x, node.y));

        x = node.x;
        y = node.y;
        closedList[x][y] = true;

        //For each neighbour starting from North-West to South-East
        for (int newX = -1; newX <= 1; newX++) {
            for (int newY = -1; newY <= 1; newY++) {
                double gNew, hNew, fNew;
                //trying to deny diagonals

                    if (isDestination(x + newX, y + newY, dest))
                    {
                        //Destination found - make path
                        allMap[x + newX][y + newY].parentX = x;
                        allMap[x + newX][y + newY].parentY = y;
                        destinationFound = true;
                        try {
                            int x = dest.x;
                            int y = dest.y;
                            std::stack<Node> path;
                            std::vector<Node> usablePath;

                            while (!(allMap[x][y].parentX == x && allMap[x][y].parentY == y)
                                   && allMap[x][y].x != -1 && allMap[x][y].y != -1)
                            {
                                path.push(allMap[x][y]);
                                int tempX = allMap[x][y].parentX;
                                int tempY = allMap[x][y].parentY;
                                x = tempX;
                                y = tempY;

                            }
                            path.push(allMap[x][y]);

                            while (!path.empty()) {
                                Node top = path.top();
                                path.pop();
                                usablePath.emplace_back(top);
                            }
                            return usablePath;
                        }
                        catch(const std::exception& e){
                            std::cout << e.what() << std::endl;
                        }
                    }
                    else if (!closedList[x + newX][y + newY])
                    {
                        gNew = node.gCost + 1.0;
                        hNew = calculateH(x + newX, y + newY, dest);
                        fNew = gNew + hNew;
                        // Check if this path is better than the one already present
                        if (allMap[x + newX][y + newY].fCost == FLT_MAX ||
                            allMap[x + newX][y + newY].fCost > fNew)
                        {
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
    if (!destinationFound) {
        //Destination not found;
        return empty;
    }
}
/*
std::vector <Node> AStar::makePath( Node allMap[][], Node dest) {
    try {
        int x = dest.x;
        int y = dest.y;
        std::stack<Node> path;
        std::vector<Node> usablePath;

        while (!(allMap[x][y].parentX == x && allMap[x][y].parentY == y)
               && allMap[x][y].x != -1 && allMap[x][y].y != -1)
        {
            path.push(allMap[x][y]);
            int tempX = allMap[x][y].parentX;
            int tempY = allMap[x][y].parentY;
            x = tempX;
            y = tempY;

        }
        path.push(allMap[x][y]);

        while (!path.empty()) {
            Node top = path.top();
            path.pop();
            usablePath.emplace_back(top);
        }
        return usablePath;
    }
    catch(const std::exception& e){
        std::cout << e.what() << std::endl;
    }
}
*/
double AStar::calculateH(int x, int y, Node dest) {

    double H = (sqrt((x - dest.x) * (x - dest.x) + (y - dest.y) * (y - dest.y)));

    return H;
}

bool AStar::isDestination(int x, int y, Node dest) {
    return x == dest.x && y == dest.y;
}

bool AStar::isValid(int x, int y) {
    for (auto obs : obstacles)
        if (x < (obs->left + obs->width) && x > obs->left && y < obs->top && y > (obs->top - obs->height))
            return false;

    return true;
}




