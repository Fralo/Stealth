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
#include "KilledEnemyObserver.hpp"
#include "StealthStatusObserver.hpp"
#include "AdvancementManagerSubject.hpp"




struct EnemyView {
    float angle;
    unsigned int distance;
    float swing;
};

class Enemy : public GameObject, public AdvancementManagerSubject{
public:
    Enemy(sf::Vector2f position, float orientation, Weapon weapon, EnemyView view,
          const std::shared_ptr<Strategy> &defaultStrategy);

    void applyDamage(int damage);

    void update(const std::list<std::shared_ptr<Object>> &objects, Player &player, TiledMap &map);

    void subscribe(std::shared_ptr<AdvancementManagerObserver> observer, const std::type_info &classInfo) override;

    void unsubscribe(std::shared_ptr<AdvancementManagerObserver> observer, const std::type_info &classInfo) override;

    void notify(const std::type_info &classInfo) override;

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

    sf::ConvexShape getSightTraigle() const;

    //new observer implementation
    std::list<std::shared_ptr<AdvancementManagerObserver>> killedEnemyObservers;
    std::list<std::shared_ptr<AdvancementManagerObserver>> stealthStatusObservers;


};


#endif //STEALTH_ENEMY_HPP
