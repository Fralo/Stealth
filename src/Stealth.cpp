//
// Created by vivedo on 09/05/20.
//

#include "Stealth.hpp"

Stealth::Stealth() {
    window.create(sf::VideoMode(800, 600), "Stealth", sf::Style::Default);
    window.setFramerateLimit(30);
    window.setKeyRepeatEnabled(false);

    changeState(new LoadScreen());

    while(window.isOpen())
        if(!stateStack.empty()){
            stateStack.front()->update(*this);

            if(doPopStack) {
                doPopStack = false;
                stateStack.pop_front();
                stateStack.front()->init(*this);
            }
        }

}

void Stealth::changeState(GameState *newGameState) {
    if(!stateStack.empty())
        stateStack.front()->unload();

    stateStack.push_front(std::unique_ptr<GameState>(newGameState));
    newGameState->init(*this);
}

void Stealth::popStack() {
    doPopStack = true;
}
