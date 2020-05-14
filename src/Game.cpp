//
// Created by vivedo on 09/05/20.
//

#include "Game.hpp"

void Game::init(Stealth &stealth) {
    stealth.window.setMouseCursorVisible(false);

    map = new TiledMap(objects);
    loadMapConfig();

    view.setCenter(sf::Vector2f(player->position));

    clock.restart();
}

void Game::update(Stealth &stealth) {
    pollEvents(stealth);

    /*
     * Update objects
     */
    for (Enemy *enemy : enemies)
        enemy->update(*this);
    player->update(*this);
    cursor.update(*this, stealth.window);

    updateMapView(stealth);
    /*
     * Draw objects
     */
    stealth.window.clear();

    stealth.window.draw(*map);
    for (Enemy *enemy : enemies)
        stealth.window.draw(*enemy);
    stealth.window.draw(*player);
    stealth.window.draw(cursor);

    stealth.window.display();
}

void Game::handleEvent(Stealth &stealth, sf::Event &event) {

}

void Game::loadMapConfig() {
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
                spawn->FloatAttribute("orientation"),
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

    xml::XMLElement *playerSpawn = root->FirstChildElement("player")->FirstChildElement("spawnpoint");
    xml::XMLElement *xmlPlayerWeapon = root->FirstChildElement("player")->FirstChildElement("weapon");
    player = new Player({
                                playerSpawn->IntAttribute("x"),
                                playerSpawn->IntAttribute("y")
                        },
                        {
                                xmlPlayerWeapon->IntAttribute("rate"),
                                xmlPlayerWeapon->IntAttribute("damage")
                        });
}

/*
 * Handles game view, moving when mouse gets near border but preventing it from getting away from the TiledMap
 */
void Game::updateMapView(Stealth &stealth) {
    const unsigned int moveBorderSize = 40;
    const float movementSpeed = 0.5f;

    sf::Vector2u windowSize = stealth.window.getSize();
    float screenRatio = ((float) windowSize.x) / windowSize.y;
    view.setSize(800, 800 / screenRatio);

    sf::IntRect top(0, 0, windowSize.x, moveBorderSize);
    sf::IntRect bottom(0, windowSize.y - moveBorderSize, windowSize.x, moveBorderSize);
    sf::IntRect left(0, 0, moveBorderSize, windowSize.y);
    sf::IntRect right(windowSize.x - moveBorderSize, 0, moveBorderSize, windowSize.y);

    sf::Vector2i mouse = sf::Mouse::getPosition(stealth.window);

    if(top.contains(mouse))
        view.move(0, -movementSpeed * clock.getElapsedTime().asMilliseconds());
    else if(bottom.contains(mouse))
        view.move(0, movementSpeed * clock.getElapsedTime().asMilliseconds());
    if(right.contains(mouse))
        view.move(movementSpeed * clock.getElapsedTime().asMilliseconds(), 0);
    else if(left.contains(mouse))
        view.move(-movementSpeed * clock.getElapsedTime().asMilliseconds(), 0);

    clock.restart();

    sf::Vector2f viewSize = view.getSize();
    sf::Vector2u mapSize = map->getMapActualSize();

    /*
     * Prevent view from getting out of map
     */
    if(view.getCenter().x < viewSize.x / 2)
        view.setCenter(viewSize.x / 2, view.getCenter().y);
    else if(view.getCenter().x > mapSize.x - viewSize.x / 2)
        view.setCenter(mapSize.x - viewSize.x / 2, view.getCenter().y);
    if(view.getCenter().y < viewSize.y / 2)
        view.setCenter(view.getCenter().x, viewSize.y / 2);
    else if(view.getCenter().y > mapSize.y - viewSize.y / 2)
        view.setCenter(view.getCenter().x, mapSize.y - viewSize.y / 2);

    stealth.window.setView(view);
}
