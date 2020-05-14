//
// Created by mattia on 14/05/20.
//

#ifndef STEALTH_HUNTERSTRATEGY_HPP
#define STEALTH_HUNTERSTRATEGY_HPP


#include "Strategy.hpp"
#include "AStar.hpp"

class HunterStrategy : public Strategy {
public:
    sf::Vector2f getNextMove(GameObject &gameObject, Game &game) override;
private:

    AStar *aStar;
};


#endif //STEALTH_HUNTERSTRATEGY_HPP
