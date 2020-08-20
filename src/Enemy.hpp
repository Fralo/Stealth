//
// Created by vivedo on 09/05/20.
//

#ifndef STEALTH_ENEMY_HPP
#define STEALTH_ENEMY_HPP

#define _USE_MATH_DEFINES
#include <cmath>
#include <memory>
#include "GameObject.hpp"
#include "Strategy.hpp"
#include "Weapon.h"
#include "Player.hpp"
#include "HunterStrategy.hpp"
#include "MathHelper.hpp"
#include "EnemyShootingObserver.hpp"


class EnemyShootingObserver;

struct EnemyView {
    float angle;
    unsigned int distance;
    float swing;
};

class Enemy : public GameObject {
public:
    Enemy(sf::Vector2f position, float orientation, Weapon weapon, EnemyView view, Strategy *defaultStrategy);
    void applyDamage(int damage);
    void update(const std::list<std::shared_ptr<Object>> &objects,Player &player,TiledMap &map);
    void subscribe(EnemyShootingObserver *pointer);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Clock clock;
    std::shared_ptr<Strategy> defaultStrategy;
    std::shared_ptr<Strategy> strategy;
    EnemyView view;
    double orientation;
    double orientationTarget;
    double sightSwingVariation = 0;
    Weapon weapon;
    std::list<EnemyShootingObserver *> listESO;

    sf::ConvexShape getSightTraigle() const;
};


#endif //STEALTH_ENEMY_HPP
