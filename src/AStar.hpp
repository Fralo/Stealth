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
    AStar(std::forward_list<Obstacle*> &obs, sf::Vector2u mapSize, sf::Vector2u tSize);
    std::vector<Node> getPath(Node hunter,Node target);

private:
    AStar() = default;
    sf::Vector2u mapSize;
    sf::Vector2u tileSize;
    std::forward_list<Obstacle*> &obstacles;

    std::vector<Node> makePath(Node map[15][15], Node dest);
    bool isDestination(int x, int y, Node dest);
    bool isValid(int x, int y);
    double calculateH(int x, int y, Node dest);
};

#endif //STEALTH_ASTAR_HPP
