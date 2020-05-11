//
// Created by vivedo on 09/05/20.
//

#include "Game.hpp"
#include "SeekStrategy.hpp"

void Game::init(Stealth &stealth) {

    new TiledMap();
    loadMap();
}

void Game::update(Stealth &stealth) {
    pollEvents(stealth);

    stealth.window.clear();

    // TODO: game

    stealth.window.draw(map);

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
        std::string sight_radius = enemy->Attribute("sight-radius") == nullptr ? "none" : enemy->Attribute("sight-radius");
        std::string sight_distance = enemy->Attribute("sight-distance") == nullptr ? "none" : enemy->Attribute("sight-distance");
        std::string swing = enemy->Attribute("swing") == nullptr ? "none" : enemy->Attribute("swing");
        int spawnX, spawnY, spawnOr;
        tinyxml2::XMLElement* spawn = enemy->FirstChildElement("spawnpoint")->ToElement();
        if(spawn != nullptr) {
            spawnX = atoi(spawn->Attribute("x"));
            spawnY = atoi(spawn->Attribute("y"));
            spawnOr = atoi(spawn->Attribute("r"));
        }

        std::forward_list<sf::Vector2i> locations;
        //<movement> <location x="400" y="400"/>
        tinyxml2::XMLNode* locationNode = enemy->FirstChildElement("movement")->FirstChildElement("location");
        sf::Vector2i a;
        tinyxml2::XMLElement* loc;
        while(locationNode != nullptr) {
            loc = locationNode->ToElement();
            a.x = atoi(loc->Attribute("x"));
            a.y = atoi(loc->Attribute("y"));
            locations.push_front(a);
            locationNode = locationNode->NextSibling();
        }
        Strategy* strategy = new SeekStrategy(spawnX, spawnY, spawnOr, locations, this->obstacles);

        //<weapon rate="1" damage="10"/>
        tinyxml2::XMLElement* weapon = enemy->FirstChildElement("weapon")->ToElement();
        Weapon we;
        if(weapon != nullptr) {
            we.rate = atoi(weapon->Attribute("rate"));
            we.damage = atoi(weapon->Attribute("damage"));

        }
        this->enemies.push_front(new Enemy(*strategy,we));
    }
}
