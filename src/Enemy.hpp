//
// Created by vivedo on 09/05/20.
//

#ifndef STEALTH_ENEMY_HPP
#define STEALTH_ENEMY_HPP


#include "GameObject.hpp"
#include "Strategy.hpp"

class Enemy : GameObject {
public:
    Enemy(Strategy &defaultStrategy);

    void update() override;

    void draw(sf::RenderWindow window) override;

private:
    const Strategy *defaultStrategy;
};


#endif //STEALTH_ENEMY_HPP
