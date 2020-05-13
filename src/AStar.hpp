//
// Created by mattia on 10/05/20.
//

#ifndef STEALTH_ASTAR_HPP
#define STEALTH_ASTAR_HPP

#include <vector>
#include <float.h>
#include <math.h>
#include <forward_list>
#include <stack>
#include <iostream>
#include "Obstacle.hpp"

struct Node{
    int x;
    int y;
    int parentX;
    int parentY;
    float hCost;
    float gCost;
    float fCost;
};

class AStar {
public:


    AStar(std::forward_list<Obstacle> &obs,sf::Vector2<unsigned int> mapSize);
    std::vector<Node> getPath(Node hunter,Node target);

private:
    std::vector<Node> makePath( Node *map, Node dest);
    bool isDestination(int x, int y, Node dest);
    bool isValid(int x, int y);
    double calculateH(int x, int y, Node dest);

    sf::Vector2<unsigned int> mapSize;
    std::forward_list<Obstacle> *obstacles;
};

#endif //STEALTH_ASTAR_HPP
