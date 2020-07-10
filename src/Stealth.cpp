//
// Created by vivedo on 09/05/20.
//

#include "Stealth.hpp"

Stealth::Stealth() {
    window.create(sf::VideoMode(800, 600), "Stealth", sf::Style::Default);
    window.setFramerateLimit(30);
    //window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    changeState(new LoadScreen());

    while(window.isOpen()) {
        if(!stateStack.empty())
            stateStack.front()->update(*this);
    }

}

void Stealth::changeState(GameState *newGameState) {
    stateStack.push_front(newGameState);
    newGameState->init(*this);
}
