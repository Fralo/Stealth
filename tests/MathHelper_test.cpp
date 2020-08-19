//
// Created by vivedo on 11/08/20.
//

#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>
#include "../src/MathHelper.hpp"
#include "../src/Weapon.h"
#include "../src/Enemy.hpp"

TEST_CASE("Distance Between Two Points", "[MathHelper]") {

    sf::Vector2f p1;
    sf::Vector2f p2;

    p1.x = 2;
    p1.y = 2;
    p2.x = 4;
    p2.y = 2;
    REQUIRE(MathHelper::distanceBetweenTwoPoints(p1,p2) == 2);
}

TEST_CASE("Check Line Intersection", "[MathHelper]") {
    REQUIRE(MathHelper::checkLineIntersection(1,1,5,1,3,-1,3,5) == true);
}

TEST_CASE("Has Line Of Sight", "[MathHelper]") {
    sf::Vector2f p1;
    sf::Vector2f p2;

    p1.x = 5;
    p1.y = -1;
    p2.x = 5;
    p2.y = 11;
    sf::Rect<float> testRect;
    testRect.height = 10;
    testRect.top = 10;
    testRect.left = 0;
    testRect.width = 15;

    REQUIRE(MathHelper::hasLineOfSight(p1,p2,testRect));

}

TEST_CASE("Check if a target is inside a polygon", "[MathHelper]") {
    sf::Vector2f position;
    float orientation;
    Weapon weapons;
    EnemyView view;
    Strategy *defaultStrategy;

    std::vector<sf::Vector2f> coordinates;
    sf::Vector2f target;


    coordinates.push_back({1,1});
    coordinates.push_back({1,5});
    coordinates.push_back({5,1});

    REQUIRE(MathHelper::isTargetInside(coordinates,{2,2}) == true );


    BENCHMARK("Enemy::isTargetInside()") {
                                             return  MathHelper::isTargetInside(coordinates,{2,2});
                                         };

}


