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

    void simulateObjectPickUp();

    void simulateObjectDropDown(int itemToRelease);

    int getEnemiesNumber();

    bool getGameStatus();

private:
    bool isGameRunning;
};


#endif //STEALTH_GAMETEST_HPP
