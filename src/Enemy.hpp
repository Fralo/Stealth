//
// Created by vivedo on 09/05/20.
//

#ifndef STEALTH_ENEMY_HPP
#define STEALTH_ENEMY_HPP


#include "GameObject.hpp"
#include "Strategy.hpp"
#include "Weapon.h"
#include "Player.hpp"
#include "Game.hpp"

class Enemy : GameObject {
public:
    Enemy(Strategy &defaultStrategy, Weapon weapon);

    void update(Game &game) override;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    const Strategy *defaultStrategy;
    Weapon weapon;
};


#endif //STEALTH_ENEMY_HPP
