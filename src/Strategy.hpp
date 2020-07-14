//
// Created by vivedo on 09/05/20.
//

#ifndef STEALTH_STRATEGY_HPP
#define STEALTH_STRATEGY_HPP

#include <SFML/System.hpp>
#include "GameObject.hpp"
#include "Object.hpp"
#include "Player.hpp"

class Strategy {
public:
    /*
     * Returns a vector of length 1 indicating direction of next movement
     */
    virtual sf::Vector2f getNextMove(GameObject &gameObject, const std::list<std::shared_ptr<Object>> &objects,Player &player,TiledMap &map) = 0;
};


#endif //STEALTH_STRATEGY_HPP
