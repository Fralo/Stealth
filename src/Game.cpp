//
// Created by vivedo on 09/05/20.
//

#include "Game.hpp"

void Game::init(Stealth &stealth) {
    stealth.window.setMouseCursorVisible(false);

    map = new TiledMap(objects);
    loadMapConfig();

    view.setCenter(sf::Vector2f(player->position));

    levelMusic.openFromFile(resource("music/Stealth_level1.ogg"));
    levelMusic.setLoop(true);
    levelMusic.setVolume(20);
    levelMusic.play();

    clock.restart();
}

void Game::update(Stealth &stealth) {
    pollEvents(stealth);

    /*
     * Updates and draws scene 1000 / TICKDELAY times per second
     */
    if(tickClock.getElapsedTime().asMilliseconds() <= TICKDELAY)
        return;
    tickClock.restart();

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
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
       player->setNextPos(stealth.window.mapPixelToCoords(sf::Mouse::getPosition(stealth.window)));
    }
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
    loadEnemies(root);

    xml::XMLElement *playerSpawn = root->FirstChildElement("player")->FirstChildElement("spawnpoint");
    xml::XMLElement *xmlPlayerWeapon = root->FirstChildElement("player")->FirstChildElement("weapon");
    player = new Player({
                                playerSpawn->FloatAttribute("x"),
                                playerSpawn->FloatAttribute("y")
                        },
                        {
                                xmlPlayerWeapon->IntAttribute("rate"),
                                xmlPlayerWeapon->IntAttribute("damage")
                        });
}

void Game::loadEnemies(xml::XMLElement *root) {
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
                        spawn->FloatAttribute("x"),
                        spawn->FloatAttribute("y")
                },
                spawn->FloatAttribute("orientation"),
                {
                        weapon->IntAttribute("rate"),
                        weapon->IntAttribute("damage"),
                        weapon->IntAttribute("distance")
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

    if (top.contains(mouse))
        view.move(0, -movementSpeed * clock.getElapsedTime().asMilliseconds());
    else if (bottom.contains(mouse))
        view.move(0, movementSpeed * clock.getElapsedTime().asMilliseconds());
    if (right.contains(mouse))
        view.move(movementSpeed * clock.getElapsedTime().asMilliseconds(), 0);
    else if (left.contains(mouse))
        view.move(-movementSpeed * clock.getElapsedTime().asMilliseconds(), 0);

    clock.restart();

    sf::Vector2f viewSize = view.getSize();
    sf::Vector2u mapSize = map->getMapActualSize();

    /*
     * Prevent view from getting out of map
     */
    if (view.getCenter().x < viewSize.x / 2)
        view.setCenter(viewSize.x / 2, view.getCenter().y);
    else if (view.getCenter().x > mapSize.x - viewSize.x / 2)
        view.setCenter(mapSize.x - viewSize.x / 2, view.getCenter().y);
    if (view.getCenter().y < viewSize.y / 2)
        view.setCenter(view.getCenter().x, viewSize.y / 2);
    else if (view.getCenter().y > mapSize.y - viewSize.y / 2)
        view.setCenter(view.getCenter().x, mapSize.y - viewSize.y / 2);

    stealth.window.setView(view);
}
