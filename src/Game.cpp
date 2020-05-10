//
// Created by vivedo on 09/05/20.
//

#include "Game.hpp"

void Game::init(Stealth &stealth) {

    loadMap();
}

void Game::update(Stealth &stealth) {
    pollEvents(stealth);

    stealth.window.close();

    stealth.window.clear();

    // TODO: game

    stealth.window.display();
}

void Game::handleEvent(Stealth &stealth, sf::Event &event) {

}

void Game::loadMap() {
    xml::XMLDocument xml;
    xml.LoadFile("../res/maps/01.xml");

    xml::XMLElement *root = xml.FirstChildElement("stealth");
    xml::XMLElement *enemies = root->FirstChildElement("enemies");

    for(xml::XMLElement *enemy = enemies->FirstChildElement("enemy"); enemy != nullptr; enemy = enemy->NextSiblingElement("enemy")) {
        std::cout << enemy->Attribute("sight-radius") << std::endl;
    }
}
