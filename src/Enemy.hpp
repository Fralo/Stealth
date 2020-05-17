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
    Enemy(sf::Vector2f position, float orientation, Weapon weapon, EnemyView view, Strategy *defaultStrategy);
    void update(Game &game) override;
    EnemyView view;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Clock clock;
    Strategy *defaultStrategy;
    Strategy *strategy;
    float orientation;
    float orientationTarget;
    float sightSwingVariation = 0;
    Weapon weapon;

    sf::ConvexShape getSightTraigle() const;
    std::vector<sf::Vector2f> getVertices() const;
    sf::Vector2f getAbsoluteCoordinates(sf::Vector2f relatives) const;
    float distanceFromPlayer(Game &game);
    bool isPlayerOnView(std::vector<sf::Vector2f> coordinates, Game &game);
    double Angle2D(float x1, float y1, float x2, float y2);
};


#endif //STEALTH_ENEMY_HPP
