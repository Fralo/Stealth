//
// Created by vivedo on 09/05/20.
//

#include "Stealth.hpp"

Stealth::Stealth() {
    window.create(sf::VideoMode(800, 600), "Stealth", sf::Style::Default);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    changeState(new LoadScreen());

    while(window.isOpen()) {
        gameState->update(*this);

        delete garbageState;
        garbageState = nullptr;
    }

}

void Stealth::changeState(GameState *newGameState) {
    garbageState = gameState;
    gameState = newGameState;
    gameState->init(*this);
}
