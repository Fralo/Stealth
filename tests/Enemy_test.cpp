//
// Created by mattia on 20/05/20.
//

#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch.hpp>
#include "../src/Enemy.hpp"

TEST_CASE("Check if a target is inside a polygon", "[Enemy]") {

    sf::Vector2f position;
    float orientation;
    Weapon weapons;
    EnemyView view;
    Strategy *defaultStrategy;

    std::vector<sf::Vector2f> coordinates;
    sf::Vector2f target;

    auto&& enemy = new Enemy(position, orientation, weapons, view,defaultStrategy);

    coordinates.push_back({1,1});
    coordinates.push_back({1,5});
    coordinates.push_back({5,1});

    REQUIRE( enemy->isTargetInside(coordinates,{2,2}) == true );


    BENCHMARK("Enemy::isTargetInside()") {
                                    return  enemy->isTargetInside(coordinates,{2,2});
                                };
}