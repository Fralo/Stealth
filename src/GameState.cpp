//
// Created by vivedo on 10/05/20.
//

#include "GameState.hpp"
#include "Stealth.hpp"

void GameState::pollEvents(Stealth &stealth) {
    sf::Event event;
    while(stealth.window.pollEvent(event))
        switch(event.type) {
            case sf::Event::Closed:
                stealth.window.close();
                break;
            case sf::Event::Resized:
                stealth.window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                break;
            default:
                handleEvent(stealth, event);
                break;
        }
}

