//
// Created by mattia on 20/05/20.
//

#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>

#include "../src/GameTest.hpp"

TEST_CASE("Enemy murdur by a player", "[Game]") {
    std::shared_ptr<GameTest> gameTest = std::make_shared<GameTest>();

    int enemiesBefore = gameTest->getEnemiesNumber();
    for(int i = 0; i<10;i++)
        gameTest->simulateClickOnEnemy();
    int enemiesAfter = gameTest->getEnemiesNumber();


    REQUIRE( enemiesAfter < enemiesBefore);
}


