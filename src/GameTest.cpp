//
// Created by mattia on 08/09/20.
//

#include "GameTest.hpp"

void GameTest::simulateClickOnEnemy() {
    player->shootEnemy(enemies.front());
}

int GameTest::getEnemiesNumber() {
    return std::distance(enemies.begin(),enemies.end());
}
