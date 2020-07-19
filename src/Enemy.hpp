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
    bool isTargetInside(std::vector<sf::Vector2f> coordinates, sf::Vector2f target);

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
    std::vector<sf::Vector2f> getViewVertices() const;
    std::vector<sf::Vector2f> getFireVertices() const;
    sf::Vector2f getAbsoluteCoordinates(sf::Vector2f relatives) const;
    static float distanceBetweenTwoPoints(sf::Vector2f p1,sf::Vector2f p2);
    static double Angle2D(double x1, double y1, double x2, double y2);
    bool hasLineOfSight(const std::list<std::shared_ptr<Object>> &objects, Player &player);
    static bool checkLineIntersection(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
};


#endif //STEALTH_ENEMY_HPP
