//
// Created by vivedo on 15/05/20.
//

#ifndef STEALTH_ASTAR2_HPP
#define STEALTH_ASTAR2_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include <forward_list>
#include "Object.hpp"

#define h(node, to) ((to.x   - node.x) * (to.x   - node.x) + (to.y   - node.y) * (to.y   - node.y))

#define DIAGONAL_COST 2
#define NORMAL_COST 1

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

struct Node {
    Node *parent;
    uint8 x;
    uint8 y;
    uint16 g;
    uint32 h;

    bool operator==(const struct Node& other) const {
        return other.x == this->x && other.y == this->y;
    }

    bool operator>(const struct Node& other) const {
        return (this->g + this->h) > (other.x + other.h);
    }

    bool operator<(const struct Node& other) const {
        return (this->g + this->h) < (other.x + other.h);
    }
};

class AStar2 {
public:
    AStar2(std::list<sf::IntRect> &obstacles, sf::Vector2u mapSize);

    std::forward_list<sf::Vector2<uint8>> * getPath(sf::Vector2<uint8> a, sf::Vector2<uint8> b);

private:
    const std::list<sf::IntRect> &obstacles;
    const sf::Vector2u mapSize;

    std::list<Node> openList;
    std::list<Node> closedList;

    std::forward_list<sf::Vector2<uint8>> * getPath(Node from, Node to);
    bool isValid(uint16 x, uint16 y) const;
    bool isBlocked(uint8 x, uint8 y);

};


#endif //STEALTH_ASTAR2_HPP
