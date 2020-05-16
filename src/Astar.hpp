//
// Created by vivedo on 15/05/20.
//

#ifndef STEALTH_ASTAR_HPP
#define STEALTH_ASTAR_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include <forward_list>
#include <cmath>
#include <algorithm>
#include "Object.hpp"

#define DIAGONAL_COST 14 // √2
#define NORMAL_COST 10

#define manhattanH(node, to) (std::abs(node.x - to.x) + std::abs(node.y - to.y))
#define euclideanHSquared(node, to) ((to.x   - node.x) * (to.x   - node.x) + (to.y   - node.y) * (to.y   - node.y))
#define uniformDiagonalH(node, to) (NORMAL_COST * std::max(std::abs(node.x - to.x), std::abs(node.y - to.y)))

#define dmin(node, to) std::min(std::abs(node.x - to.x), std::abs(node.y - to.y))
#define dmax(node, to) std::max(std::abs(node.x - to.x), std::abs(node.y - to.y))
#define diagonalH(node, to) (DIAGONAL_COST * dmin(node, to) + NORMAL_COST * (dmax(node, to) - dmin(node, to)))

#define h(node, to) diagonalH(node, to)

typedef sf::Vector2<uint8_t> Vector2u8;
typedef std::forward_list<Vector2u8> Path;

class Astar {
public:
    Astar(std::forward_list<sf::IntRect> &obstacles, Vector2u8 mapSize);

    Path *getPath(Vector2u8 a, Vector2u8 b);

private:
    struct Node {
        Node *parent;
        uint8_t x;
        uint8_t y;
        uint16_t g;
        uint32_t f;

        /*
         * Equality compares coordinates
         */
        bool operator==(const struct Node& other) const {
            return other.x == this->x && other.y == this->y;
        }
    };

    const std::forward_list<sf::IntRect> &obstacles;
    const sf::Vector2<uint8_t> mapSize;
    std::forward_list<Node*> openList;
    std::forward_list<Node*> closedList;

    bool isValid(uint16_t x, uint16_t y) const;
    bool isBlocked(uint8_t x, uint8_t y);
    Path *getPath(Node *from, Node *to);
    void clearLists();
};


#endif //STEALTH_ASTAR_HPP
