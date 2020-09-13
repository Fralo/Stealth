//
// Created by mattia on 09/09/20.
//

#define CATCH_CONFIG_ENABLE_BENCHMARKING

#include <catch2/catch.hpp>
#include "GameTest.hpp"

TEST_CASE("Killing of an enemy by the player", "[Game]") {
    std::shared_ptr<GameTest> gameTest = std::make_shared<GameTest>();
    gameTest->init();

    int enemiesBefore = gameTest->getEnemiesNumber();
    for (int i = 0; i < 11; i++)
        gameTest->simulateClickOnEnemy();

    gameTest->update();
    int enemiesAfter = gameTest->getEnemiesNumber();

    REQUIRE(enemiesBefore > enemiesAfter);
}

TEST_CASE("Win the mission","[Game]")
{
    std::shared_ptr<GameTest> gameTest = std::make_shared<GameTest>();
    gameTest->init();
    gameTest->simulateObjectPickUp();
    gameTest->simulateObjectPickUp();

    gameTest->simulateObjectDropDown(1);
    gameTest->update();
    gameTest->simulateObjectDropDown(1);
    gameTest->update();

    REQUIRE(!gameTest->getGameStatus());

}