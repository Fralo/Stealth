//
// Created by mattia on 10/05/20.
//

#ifndef STEALTH_ASTAR_HPP
#define STEALTH_ASTAR_HPP

#include <vector>
#include <float.h>
#include <math.h>

struct Node{
    int x;
    int y;
    int parentX;
    int parentY;
    float gCost;
    float fCost;
};

class AStar {
public:
    AStar(){};
    std::vector<Node> getPath(Node hunter,Node target);//TODO: Add the GameMap to the argument

private:
    bool isDestination(int x, int y, Node dest);
    bool isValid(int x, int y);//TODO: Add the GameMap to the argument
};

#endif //STEALTH_ASTAR_HPP
