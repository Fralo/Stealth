//
// Created by vivedo on 15/05/20.
//

#ifndef STEALTH_ASTAR2_HPP
#define STEALTH_ASTAR2_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include <forward_list>
#include <cmath>
#include <algorithm>
#include "Object.hpp"

#define DIAGONAL_COST 14
#define NORMAL_COST 10

#define manhattanH(node, to) (std::abs(node.x - to.x) + std::abs(node.y - to.y))
#define euclideanHSquared(node, to) ((to.x   - node.x) * (to.x   - node.x) + (to.y   - node.y) * (to.y   - node.y))
#define uniformDiagonalH(node, to) (NORMAL_COST * std::max(std::abs(node.x - to.x), std::abs(node.y - to.y)))

#define dmin(node, to) std::min(std::abs(node.x - to.x), std::abs(node.y - to.y))
#define dmax(node, to) std::max(std::abs(node.x - to.x), std::abs(node.y - to.y))
#define diagonalH(node, to) (DIAGONAL_COST * dmin(node, to) + NORMAL_COST * (dmax(node, to) - dmin(node, to)))

#define h(node, to) diagonalH(node, to)

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

typedef std::forward_list<sf::Vector2<uint8>> Path;

struct Node {
    Node *parent;
    uint8 x;
    uint8 y;
    uint16 g;
    uint32 f;

    /*
     * Equality compares coordinates
     */
    bool operator==(const struct Node& other) const {
        return other.x == this->x && other.y == this->y;
    }

    // maj/min compares f value
    bool operator>(const struct Node& other) const {
        return this->f > other.f;
    }

    bool operator<(const struct Node& other) const {
        return this->f < other.f;
    }
};

class AStar2 {
public:
    AStar2(std::forward_list<sf::IntRect> &obstacles, sf::Vector2u mapSize);

    Path *getPath(sf::Vector2<uint8> a, sf::Vector2<uint8> b);

private:
    const std::forward_list<sf::IntRect> &obstacles;
    const sf::Vector2u mapSize;
    std::forward_list<Node*> openList;
    std::forward_list<Node*> closedList;

    bool isValid(uint16 x, uint16 y) const;
    bool isBlocked(uint8 x, uint8 y);
    Path *getPath(Node *from, Node *to);
    void clearLists();

};


#endif //STEALTH_ASTAR2_HPP
