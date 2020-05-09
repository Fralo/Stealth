//
// Created by vivedo on 09/05/20.
//

#ifndef STEALTH_ENEMY_HPP
#define STEALTH_ENEMY_HPP


#include "GameObject.hpp"

class Enemy : GameObject {
    void update() override;

    void draw(sf::RenderWindow window) override;

};


#endif //STEALTH_ENEMY_HPP
