//
// Created by vivedo on 09/05/20.
//

#ifndef STEALTH_ENEMY_HPP
#define STEALTH_ENEMY_HPP

#define _USE_MATH_DEFINES
#include <cmath>
#include "GameObject.hpp"
#include "Strategy.hpp"
#include "Weapon.h"
#include "Player.hpp"
#include "Game.hpp"

struct EnemyView {
    float angle;
    unsigned int distance;
    float swing;
};

class Enemy : public GameObject {
public:
    Enemy(sf::Vector2i position, float orientation, Weapon weapon, EnemyView view, Strategy *defaultStrategy);
    void update(Game &game) override;
    EnemyView view;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Clock clock;
    Strategy *defaultStrategy;
    Strategy *strategy;
    float orientation;
    float sightSwingVariation = 0;
    Weapon weapon;

    sf::ConvexShape getSightTraigle() const;
};


#endif //STEALTH_ENEMY_HPP
