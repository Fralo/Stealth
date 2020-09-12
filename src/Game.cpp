//
// Created by vivedo on 09/05/20.
//

#include "Game.hpp"
#include "WonGameOverScreen.hpp"

void Game::init(Stealth &stealth) {
    killedEnemyObserver = std::make_shared<KilledEnemyObserver>();
    stealthStatusObserver = std::make_shared<StealthStatusObserver>();
    stealth.window.setMouseCursorVisible(false);

    map = std::make_shared<TiledMap>(resource("maps/02-map.tmx"), objects);

    xml::XMLDocument xml;
    xml::XMLError error = xml.LoadFile(resource("maps/01.xml"));

    if (error != tinyxml2::XML_SUCCESS) {
        std::cout << "Error opening map config file" << std::endl;
        throw std::exception();
    } else
        std::cout << "Map config file opened" << std::endl;

    xml::XMLElement *root = xml.FirstChildElement("stealth");
    loadMapConfig(root);

    gameView.setCenter(sf::Vector2f(player->getPos()));

    levelMusic.openFromFile(resource("music/Stealth_level1.ogg"));
    levelMusic.setLoop(true);
    levelMusic.setVolume(20);
    levelMusic.play();

    denyMoveSfxBuffer.loadFromFile(resource("music/denymove.ogg"));
    denyMoveSfx.setBuffer(denyMoveSfxBuffer);
    inventory = std::make_shared<Inventory>();
    gameViewClock.restart();


}

void Game::update(Stealth &stealth) {
    pollEvents(stealth);

    /*
     * Updates and draws scene 1000 / TICKDELAY times per second
     */
    if (tickClock.getElapsedTime().asMilliseconds() <= TICKDELAY)
        return;
    tickClock.restart();
    /*
     * Update objects
     */
    for (const std::shared_ptr<Enemy> &enemy : enemies)
        enemy->update(objects, *player, *map);
    player->update(objects, *map);

    cursor.update(stealth.window, objects, enemies, player);
    updateViews(stealth);
    stealth.window.setView(gameView);

    /*
     * Check player life
     */

    if (player->getHealth() == 0) {
        stealth.changeState(new WonGameOverScreen(killedEnemyObserver->enemyKilled,
                                                  stealthStatusObserver->isStealth, false));
        levelMusic.stop();
    }

    /*
     * Check enemy life
     */
    for (const std::shared_ptr<Enemy> &e : enemies) {
        if (e->getHealth() == 0) {
            enemies.remove(e);
            break;
        }
    }
    /*
     * Check target object life
     */
    for (auto &&o : this->objects)
        if (o->properties.isTarget && o->getHealth() == 0) {
            stealth.changeState(new WonGameOverScreen(killedEnemyObserver->enemyKilled,
                                                      stealthStatusObserver->isStealth, true));
            levelMusic.stop();
        }

    /*
     * Draw objects
     */
    stealth.window.clear();

    stealth.window.draw(*map);

    //Check if player can take an item from the ground
    for (std::shared_ptr<Object> &obj : this->objects) {
        if (obj->properties.collectible && obj->getAbsCollisionBox().contains(player->getPos()))
            if (inventory->addObject(obj)) {
                this->objects.remove(obj);
                break;
            }
    }

    // Create an ordered list of GameObjects in order to draw them accordingly to their y coord
    std::list<std::shared_ptr<GameObject>> gameObjects;
    auto gameObjectCmp = [](const std::shared_ptr<GameObject> &a, const std::shared_ptr<GameObject> &b) {
        return a->getAbsDrawingCenter().y < b->getAbsDrawingCenter().y;
    };

    gameObjects.insert(std::lower_bound(gameObjects.begin(), gameObjects.end(), player, gameObjectCmp), player);
    for (const std::shared_ptr<Enemy> &enemy : enemies)
        gameObjects.insert(std::lower_bound(gameObjects.begin(), gameObjects.end(), enemy, gameObjectCmp), enemy);
    for (const std::shared_ptr<Object> &object : objects)
        gameObjects.insert(std::lower_bound(gameObjects.begin(), gameObjects.end(), object, gameObjectCmp), object);

    for (const std::shared_ptr<GameObject> &gameObject : gameObjects) {
        stealth.window.draw(*gameObject);

#ifdef STEALTH_GRAPHIC_DEBUG
        sf::RectangleShape re({50, 1});
        re.setPosition(gameObject->getAbsDrawingCenter() - sf::Vector2f(25, 0));
        re.setFillColor(sf::Color::White);
        stealth.window.draw(re);
        re.setSize({1, 50});
        re.setPosition(gameObject->getAbsDrawingCenter() - sf::Vector2f(0, 25));
        stealth.window.draw(re);
#endif
    }
    /*
     * gui view
     */
    stealth.window.setView(guiView);
    stealth.window.draw(*inventory);
    std::forward_list<std::shared_ptr<Object>> inventoryObjects = inventory->getInventory();
    for (const std::shared_ptr<Object> &item : inventoryObjects)
        stealth.window.draw(*item);
    stealth.window.setView(gameView);
    stealth.window.draw(cursor);
    stealth.window.display();
}

void Game::handleEvent(Stealth &stealth, sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) { // click
        if (cursor.getPointedElement().pointedElementType == ENEMY) {
            player->shootEnemy(cursor.getPointedElement().pointedElementObject);
        } else if (cursor.getPointedElement().pointedElementType == ITEM) {
            player->setTarget(cursor.getPointedElement().pointedElementObject);
        } else if (cursor.getPointedElement().pointedElementType != OBSTACLE)
            player->setTarget(stealth.window.mapPixelToCoords(sf::Mouse::getPosition(stealth.window)));
        else //It's an obstacle
            denyMoveSfx.play();
    } else if (event.type == sf::Event::KeyReleased) {
        int itemToRelease = 0;
        switch (event.key.code) {
            case sf::Keyboard::Num1:
                itemToRelease = 1;
                break;
            case sf::Keyboard::Num2:
                itemToRelease = 2;
                break;
            case sf::Keyboard::Num3:
                itemToRelease = 3;
                break;
            default:
                break;
        }
        if (itemToRelease != 0) {
            std::shared_ptr<Object> toAdd = std::move(
                    this->inventory->releaseObject(itemToRelease, this->objects, this->player->getPos()));

            if (toAdd != nullptr) {
                toAdd->setPos(player->getPos().x + player->getAbsCollisionBox().height / 2 + 1,
                              player->getPos().y + player->getAbsCollisionBox().width / 2 + 1);
                if (!toAdd->explode(this->objects))
                    this->objects.push_front(std::move(toAdd));
            } else
                denyMoveSfx.play();
        }
    }
}

void Game::loadMapConfig(xml::XMLElement *root) {
    loadEnemies(root);
    xml::XMLElement *playerSpawn = root->FirstChildElement("player")->FirstChildElement("spawnpoint");
    xml::XMLElement *xmlPlayerWeapon = root->FirstChildElement("player")->FirstChildElement("weapon");
    player = std::make_shared<Player>(
            sf::Vector2f(
                    playerSpawn->FloatAttribute("x"),
                    playerSpawn->FloatAttribute("y")
            ),
            Weapon{
                    xmlPlayerWeapon->IntAttribute("rate"),
                    xmlPlayerWeapon->IntAttribute("damage"),
                    xmlPlayerWeapon->IntAttribute("distance")
            });
}

void Game::loadEnemies(xml::XMLElement *root) {
    xml::XMLElement *xmlEnemies = root->FirstChildElement("enemies");

    for (xml::XMLElement *enemy = xmlEnemies->FirstChildElement("enemy");
         enemy != nullptr; enemy = enemy->NextSiblingElement("enemy")) {
        xml::XMLElement *spawn = enemy->FirstChildElement("spawnpoint");

        auto seekStrategy = std::make_shared<SeekStrategy>();
        xml::XMLNode *movement = enemy->FirstChildElement("movement");
        for (xml::XMLElement *location = movement->FirstChildElement("location");
             location != nullptr; location = location->NextSiblingElement("location"))
            seekStrategy->addLocation(sf::Vector2i(location->IntAttribute("x"), location->IntAttribute("y")));

        xml::XMLElement *weapon = enemy->FirstChildElement("weapon");

        enemies.push_front(std::make_shared<Enemy>(
                sf::Vector2f(
                        spawn->FloatAttribute("x"),
                        spawn->FloatAttribute("y")
                ),
                spawn->FloatAttribute("orientation"),
                Weapon{
                        weapon->IntAttribute("rate"),
                        weapon->IntAttribute("damage"),
                        weapon->IntAttribute("distance"),
                        weapon->FloatAttribute("angle"),

                },
                EnemyView{
                        enemy->FloatAttribute("sight-angle"),
                        enemy->UnsignedAttribute("sight-distance"),
                        enemy->FloatAttribute("swing")
                },
                seekStrategy));

    }
    for (std::shared_ptr<Enemy> e : enemies) {
        e->subscribe(killedEnemyObserver);
        e->subscribe(stealthStatusObserver);
    }


    std::cout << "Enemies loaded" << std::endl;
}

/*
 * Handles game view, moving when mouse gets near border but preventing it from getting away from the TiledMap
 */
void Game::updateViews(Stealth &stealth) {
    const unsigned int moveBorderSize = 40;
    const float movementSpeed = 0.5f;

    sf::Vector2u windowSize = stealth.window.getSize();
    float screenRatio = ((float) windowSize.x) / windowSize.y;
    gameView.setSize(800, 800 / screenRatio);

    sf::IntRect top(0, 0, windowSize.x, moveBorderSize);
    sf::IntRect bottom(0, windowSize.y - moveBorderSize, windowSize.x, moveBorderSize);
    sf::IntRect left(0, 0, moveBorderSize, windowSize.y);
    sf::IntRect right(windowSize.x - moveBorderSize, 0, moveBorderSize, windowSize.y);

    sf::Vector2i mouse = sf::Mouse::getPosition(stealth.window);

    if (top.contains(mouse))
        gameView.move(0, -movementSpeed * gameViewClock.getElapsedTime().asMilliseconds());
    else if (bottom.contains(mouse))
        gameView.move(0, movementSpeed * gameViewClock.getElapsedTime().asMilliseconds());
    if (right.contains(mouse))
        gameView.move(movementSpeed * gameViewClock.getElapsedTime().asMilliseconds(), 0);
    else if (left.contains(mouse))
        gameView.move(-movementSpeed * gameViewClock.getElapsedTime().asMilliseconds(), 0);

    gameViewClock.restart();

    sf::Vector2f viewSize = gameView.getSize();
    sf::Vector2u mapSize = map->getMapActualSize();

    /*
     * Prevent view from getting out of map
     */
    if (gameView.getCenter().x < viewSize.x / 2)
        gameView.setCenter(viewSize.x / 2, gameView.getCenter().y);
    else if (gameView.getCenter().x > mapSize.x - viewSize.x / 2)
        gameView.setCenter(mapSize.x - viewSize.x / 2, gameView.getCenter().y);
    if (gameView.getCenter().y < viewSize.y / 2)
        gameView.setCenter(gameView.getCenter().x, viewSize.y / 2);
    else if (gameView.getCenter().y > mapSize.y - viewSize.y / 2)
        gameView.setCenter(gameView.getCenter().x, mapSize.y - viewSize.y / 2);

    guiView.setSize(windowSize.x, windowSize.x);
    guiView.setCenter(windowSize.x / 2, windowSize.x / 2);
}
