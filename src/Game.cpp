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
            spawnX = spawn->IntAttribute("x");
            spawnY = spawn->IntAttribute("y");
            spawnOr = spawn->IntAttribute("r");
        }

        std::forward_list<sf::Vector2i> locations;
        tinyxml2::XMLNode* locationNode = enemy->FirstChildElement("movement")->FirstChildElement("location");
        sf::Vector2i a;
        tinyxml2::XMLElement* loc;
        while(locationNode != nullptr) {
            loc = locationNode->ToElement();
            a.x = loc->IntAttribute("x");
            a.y = loc->IntAttribute("y");
            locations.push_front(a);
            locationNode = locationNode->NextSibling();
        }
        Strategy* strategy = new SeekStrategy(spawnX, spawnY, spawnOr,map.getMapSize(), locations, this->obstacles);
        tinyxml2::XMLElement* weapon = enemy->FirstChildElement("weapon")->ToElement();
        Weapon we;
        if(weapon != nullptr) {
            we.rate = weapon->IntAttribute("rate");
            we.damage = weapon->IntAttribute("damage");

        } else {
            we.damage = 10; //FIXME set the deafault demage
            we.rate = 1;
        }
        this->enemies.push_front(new Enemy(*strategy,we));
    }

    std::cout << "Enemies loaded" << std::endl;
}
