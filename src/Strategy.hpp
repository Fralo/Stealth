//
// Created by vivedo on 09/05/20.
//

#ifndef STEALTH_STRATEGY_HPP
#define STEALTH_STRATEGY_HPP

#include <SFML/System.hpp>
#include "GameObject.hpp"

class Strategy {
public:
    /*
     * Returns direction vector entity has to follow
     */
    virtual sf::Vector2f getNextMove(GameObject &gameObject) = 0;
};


#endif //STEALTH_STRATEGY_HPP
