//
// Created by vivedo on 09/05/20.
//

#include "Game.hpp"

void Game::init(Stealth &stealth) {

}

void Game::update(Stealth &stealth) {
    pollEvents(stealth);

    stealth.window.clear();

    // TODO: game

    stealth.window.display();
}

void Game::handleEvent(Stealth &stealth, sf::Event &event) {

}
