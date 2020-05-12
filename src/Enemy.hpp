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

struct EnemyView {
    float radius;
    unsigned int distance;
    float swing;
};

class Enemy : GameObject {
public:
    Enemy(sf::Vector2i position, float orientation, Weapon weapon, EnemyView view, Strategy *defaultStrategy);
    void update(Game &game) override;
    EnemyView view;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    Strategy *defaultStrategy;
    Strategy *strategy;
    float orientation;
    Weapon weapon;
};


#endif //STEALTH_ENEMY_HPP
