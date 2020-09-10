//
// Created by mattia on 08/09/20.
//

#ifndef STEALTH_GAMETEST_HPP
#define STEALTH_GAMETEST_HPP


#include "../src/Game.hpp"

class GameTest : public Game {
public:
    void init();

    void update();

    void simulateClickOnEnemy();

    int getEnemiesNumber();
};


#endif //STEALTH_GAMETEST_HPP
