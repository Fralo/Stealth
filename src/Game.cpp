//
// Created by vivedo on 09/05/20.
//

#include "Game.hpp"

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

        std::cout << enemy->Name() << ":     ";
        std::string sight_radius = enemy->Attribute("sight-radius") == nullptr ? "none" : enemy->Attribute("sight-radius");
        std::string sight_distance = enemy->Attribute("sight-distance") == nullptr ? "none" : enemy->Attribute("sight-distance");
        std::string swing = enemy->Attribute("swing") == nullptr ? "none" : enemy->Attribute("swing");
        std::cout << sight_radius << " " <<sight_distance << " " << swing << std::endl;

        //<spawnpoint x="400" y="400" r="0.25"/>
        tinyxml2::XMLElement* spawn = enemy->FirstChildElement("spawnpoint")->ToElement();

        if(spawn != nullptr) {
            std::cout << spawn->Attribute("x") << " " << spawn->Attribute("y") << " " << spawn->Attribute("r") << std::endl;
        }

        std::forward_list<sf::Vector2i> locations;
        //<movement> <location x="400" y="400"/>
        tinyxml2::XMLNode* locationNode = enemy->FirstChildElement("movement")->FirstChildElement("location");
        sf::Vector2i a;
        while(locationNode != nullptr) {
            tinyxml2::XMLElement* loc = locationNode->ToElement();
            std::cout << "LocationNode: " << std::endl << loc->Attribute("x") << " " << loc->Attribute("y") <<std::endl;
            a.x = atoi(loc->Attribute("x"));
            a.y = atoi(loc->Attribute("y"));
            locations.insert_after(locations.end(), a);
            locationNode = locationNode->NextSibling();
        }


        //<weapon rate="1" damage="10"/>
        tinyxml2::XMLElement* weapon = enemy->FirstChildElement("weapon")->ToElement();
        if(weapon != nullptr) {
            std::cout << weapon->Attribute("rate") << " " << weapon->Attribute("damage") <<std::endl;
        }
    }
}
