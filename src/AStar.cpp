//
// Created by mattia on 10/05/20.
//

#include "AStar.hpp"

std::vector<Node> AStar::getPath(Node hunter, Node dest) {

    std::vector<Node> empty;
    if (!isValid(dest.x, dest.y)) {
        //Destination is an obstacle;
        return empty;
    }
    if (isDestination(hunter.x, hunter.y, dest)) {
        //You are the destination
        return empty;
    }

    bool *closedList = new bool[mapSize.x * mapSize.y];
    Node *allMap = new Node [mapSize.x * mapSize.y];


    for (int x = 0; x < (mapSize.x); x++) {
        for (int y = 0; y < (mapSize.y); y++) {
            allMap[x * mapSize.y + y].fCost = FLT_MAX;
            allMap[x * mapSize.y + y].gCost = FLT_MAX;
            allMap[x * mapSize.y + y].hCost = FLT_MAX;
            allMap[x * mapSize.y + y].parentX = -1;
            allMap[x * mapSize.y + y].parentY = -1;
            allMap[x * mapSize.y + y].x = x;
            allMap[x * mapSize.y + y].y = y;

            closedList[x * mapSize.y + y] = false;
        }
    }

    //Initialize our starting list
    int x = hunter.x;
    int y = hunter.y;
    allMap[x * mapSize.y + y].fCost = 0.0;
    allMap[x * mapSize.y + y].gCost = 0.0;
    allMap[x * mapSize.y + y].hCost = 0.0;
    allMap[x * mapSize.y + y].parentX = x;
    allMap[x * mapSize.y + y].parentY = y;

    std::vector<Node> openList;
    openList.emplace_back(allMap[x * mapSize.y + y]);
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
        closedList[x * mapSize.y + y] = true;

        //For each neighbour starting from North-West to South-East
        for (int newX = 0; newX <= 1; newX++) {
            for (int newY = 0; newY <= 1; newY++) {
                double gNew, hNew, fNew;


                if (isDestination(x + newX, y + newY, dest))
                {
                    //Destination found - make path
                    allMap[(x+newX)* mapSize.y + (y + newY)].parentX = x;
                    allMap[(x+newX)* mapSize.y + (y + newY)].parentY = y;
                    destinationFound = true;
                    return makePath(allMap, dest);
                }
                else if (!closedList[(x+newX)* mapSize.y + (y + newY)])//FIXME
                {
                    gNew = node.gCost + 1.0;
                    hNew = calculateH(x + newX, y + newY, dest);
                    fNew = gNew + hNew;
                    // Check if this path is better than the one already present
                    if (allMap[(x+newX)* mapSize.y + (y + newY)].fCost == FLT_MAX ||
                        allMap[(x+newX)* mapSize.y + (y + newY)].fCost > fNew)
                    {
                        // Update the details of this neighbour node
                        allMap[(x+newX)* mapSize.y + (y + newY)].fCost = fNew;
                        allMap[(x+newX)* mapSize.y + (y + newY)].gCost = gNew;
                        allMap[(x+newX)* mapSize.y + (y + newY)].hCost = hNew;
                        allMap[(x+newX)* mapSize.y + (y + newY)].parentX = x;
                        allMap[(x+newX)* mapSize.y + (y + newY)].parentY = y;
                        openList.emplace_back(allMap[(x+newX)* mapSize.y + (y + newY)]);
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

std::vector<Node> AStar::makePath( Node *map, Node dest) {
    try {
        int x = dest.x;
        int y = dest.y;
        std::stack<Node> path;
        std::vector<Node> usablePath;

        while (!(map[x * mapSize.y + y].parentX == x && map[x * mapSize.y + y].parentY == y)
               && map[x * mapSize.y + y].x != -1 && map[x * mapSize.y + y].y != -1)
        {
            path.push(map[x * mapSize.y + y]);
            int tempX = map[x * mapSize.y + y].parentX;
            int tempY = map[x * mapSize.y + y].parentY;
            x = tempX;
            y = tempY;

        }
        path.push(map[x * mapSize.y + y]);

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

double AStar::calculateH(int x, int y, Node dest) {

    double H = (sqrt((x - dest.x)*(x - dest.x) + (y - dest.y)*(y - dest.y)));

    return H;
}

bool AStar::isDestination(int x, int y, Node dest) {
    return x == dest.x && y == dest.y;
}

bool AStar::isValid(int x, int y) {

    for ( auto it = obstacles->begin(); it != obstacles->end(); ++it )
    {
        if(x < (it->left + it->width) && x > it->left && y < it->top && y > (it->top - it->height))
            return false;
    }
    return true;
}

AStar::AStar(std::forward_list<Obstacle> &obs, sf::Vector2<unsigned int> mSize): obstacles(&obs), mapSize(mSize){

}



