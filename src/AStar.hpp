//
// Created by mattia on 10/05/20.
//

#ifndef STEALTH_ASTAR_HPP
#define STEALTH_ASTAR_HPP

#include <vector>
#include <float.h>
#include <math.h>
#include <forward_list>
#include "Obstacle.hpp"

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


    AStar(std::forward_list<Obstacle> &obs);
    std::vector<Node> getPath(Node hunter,Node target);

private:
    std::forward_list<Obstacle> *obstacles;
    bool isDestination(int x, int y, Node dest);
    bool isValid(int x, int y);
};

#endif //STEALTH_ASTAR_HPP
