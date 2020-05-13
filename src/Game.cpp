//
// Created by vivedo on 09/05/20.
//

#include "Game.hpp"

void Game::init(Stealth &stealth) {
    stealth.window.setMouseCursorVisible(false);
    loadMap();
}

void Game::update(Stealth &stealth) {
    pollEvents(stealth);

    /*
     * Update objects
     */
    for (Enemy *enemy : enemies)
        enemy->update(*this);
    //player->update(*this);
    cursor.update(*this, stealth.window);

    /*
     * Draw objects
     */
    stealth.window.clear();

    stealth.window.draw(map.background);
    for (Enemy *enemy : enemies)
        stealth.window.draw(*enemy);
    stealth.window.draw(map.foreground);
    stealth.window.draw(cursor);

    stealth.window.display();
}

void Game::handleEvent(Stealth &stealth, sf::Event &event) {

}

void Game::loadMap() {
    xml::XMLDocument xml;
    xml::XMLError error = xml.LoadFile(resource("maps/01.xml"));

    if (error != tinyxml2::XML_SUCCESS) {
        std::cout << "Error opening map config file" << std::endl;
        throw std::exception();
    } else
        std::cout << "Map config file opened" << std::endl;


    xml::XMLElement *root = xml.FirstChildElement("stealth");
    xml::XMLElement *xmlEnemies = root->FirstChildElement("enemies");

    for (xml::XMLElement *enemy = xmlEnemies->FirstChildElement("enemy");
         enemy != nullptr; enemy = enemy->NextSiblingElement("enemy")) {
        xml::XMLElement *spawn = enemy->FirstChildElement("spawnpoint");

        auto *seekStrategy = new SeekStrategy();
        xml::XMLNode *movement = enemy->FirstChildElement("movement");
        for (xml::XMLElement *location = movement->FirstChildElement("location");
             location != nullptr; location = location->NextSiblingElement("location"))
            seekStrategy->addLocation(sf::Vector2i(location->IntAttribute("x"), location->IntAttribute("y")));

        xml::XMLElement *weapon = enemy->FirstChildElement("weapon");

        enemies.push_front(new Enemy(
                {
                        spawn->IntAttribute("x"),
                        spawn->IntAttribute("y")
                },
                spawn->FloatAttribute("r"),
                {
                        weapon->IntAttribute("rate"),
                        weapon->IntAttribute("damage")
                },
                {
                        enemy->FloatAttribute("sight-angle"),
                        enemy->UnsignedAttribute("sight-distance"),
                        enemy->FloatAttribute("swing")
                },
                seekStrategy));
    }

    std::cout << "Enemies loaded" << std::endl;
}
