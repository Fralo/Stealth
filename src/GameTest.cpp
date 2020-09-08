//
// Created by mattia on 08/09/20.
//

#include "GameTest.hpp"

void GameTest::simulateClickOnEnemy() {
    player->shootEnemy(enemies.front());
}

int GameTest::getEnemiesNumber() {
    int i;
    for(std::shared_ptr<Enemy> e : enemies)
        i++;
}
