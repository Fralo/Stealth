//
// Created by mattia on 10/05/20.
//

#include "AStar.hpp"

std::vector<Node> AStar::getPath(Node hunter, Node target) {
    /*
    std::vector<Node> empty;
    if (!isValid(dest.x, dest.y, gameMap)) {
        //Destination is an obstacle;
        return empty;
    }
    if (isDestination(hunter.x, hunter.y, dest)) {
        //You are the destination
        return empty;
    }

     bool closedList[15][15];
    //Get the overview of the map
    Node allMap[15][15];
    for (int x = 0; x < (15); x++) {
        for (int y = 0; y < (15); y++) {
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
     */
    return std::vector<Node>();
}

bool AStar::isDestination(int x, int y, Node dest) {
    return false;
}

bool AStar::isValid(int x, int y) {
    return false;
}
