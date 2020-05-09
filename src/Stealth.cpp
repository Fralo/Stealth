//
// Created by vivedo on 09/05/20.
//

#include "Stealth.hpp"

Stealth::Stealth() {
    window.create(sf::VideoMode(800, 600), "Stealth", sf::Style::Default);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    loadGame();

    while(window.isOpen()) {
        pollEvents();

        // TODO: handle events
        // TODO: update

        window.clear(sf::Color::Black);

        // TODO: draw

        window.display();
    }
}

void Stealth::pollEvents() {
    sf::Event event;
    while(window.pollEvent(event)) {
        switch(event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
            case sf::Event::KeyReleased:
                break;

            default:
                break;
        }
    }
}

void Stealth::loadGame() {
    // TODO: load map.xml and create EVERYTHING
}
