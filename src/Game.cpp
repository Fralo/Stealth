//
// Created by vivedo on 09/05/20.
//

#include "Game.hpp"

void Game::init(Stealth &stealth) {
    advancementManager = std::make_shared<AdvancementManager>(stealth);

    stealth.window.setMouseCursorVisible(false);

    map = std::make_shared<TiledMap>(resource("maps/02-map.tmx"), objects);
    loadMapConfig();

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
    advancementManager->update();

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
        else
            denyMoveSfx.play();
    } else if (event.type == sf::Event::KeyReleased) {
        int itemToRelease = 0;
        switch (event.key.code) {
            case sf::Keyboard::Num1:
                if (inventory->getSize() > 0) {
                    itemToRelease = 1;
                }
                break;
            case sf::Keyboard::Num2:
                if (inventory->getSize() > 1) {
                    itemToRelease = 2;
                }
                break;
            case sf::Keyboard::Num3:
                if (inventory->getSize() > 2) {
                    itemToRelease = 3;
                }
                break;

            default:
                break;
        }
        if (itemToRelease != 0) {
            bool canRelease = true;
            for (auto &&obj : this->objects)
                if (obj->getAbsCollisionBox().contains(player->getPos().x, player->getPos().y + 40) ||
                    obj->getAbsCollisionBox().contains(player->getPos().x + 40,
                                                       player->getPos().y)) //40 is the dimension of the square used for testing items, TODO sostituire con la dimensione del tile degli oggeti dell'inventario
                    canRelease = false;
            if (canRelease) {
                auto toAdd = std::move(this->inventory->releaseObject(itemToRelease));
                toAdd->setPos(player->getPos().x + player->getAbsCollisionBox().height / 2 + 1,
                              player->getPos().y + player->getAbsCollisionBox().width / 2 + 1);
                toAdd->properties.numberInInventory = 0;

                bool exploded = false;
                for (auto &&o : this->objects) {
                    if (o->properties.id == 1 && MathHelper::distanceBetweenTwoPoints(o->getPos(), toAdd->getPos()) < 100) {
                        o->setHealth(o->getHealth() - 50);
                        exploded = true;
                    }
                }
                if(!exploded)
                    this->objects.push_front(std::move(toAdd));
            } else
                denyMoveSfx.play();
        }
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
    loadObjects();
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
                    xmlPlayerWeapon->IntAttribute("angle")
            });

    player->subscribe(advancementManager);
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
        e->subscribeESO(advancementManager);
        e->subscribeISO(advancementManager);
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

void Game::loadObjects() {
    ObjectProperties test1;
    std::shared_ptr<Tile> t = std::make_shared<Tile>(sf::Vector2f(40, 40), sf::Rect<float>(0, 0, 40, 40));
    std::shared_ptr<Tile> t2 = std::make_shared<Tile>(sf::Vector2f(40, 40), sf::Rect<float>(0, 0, 40, 40));
    std::shared_ptr<Tile> t3 = std::make_shared<Tile>(sf::Vector2f(40, 40), sf::Rect<float>(0, 0, 40, 40));

    test1.id = 4;
    test1.collectible = true;
    test1.destroyable = false;
    std::shared_ptr<Object> obj1 = std::make_shared<Object>(t, sf::Vector2f(
            400,
            400
    ), test1);
    test1.id = 2;
    std::shared_ptr<Object> obj2 = std::make_shared<Object>(t2, sf::Vector2f(
            200,
            100
    ), test1);
    test1.id = 1;
    test1.destroyable = true;
    test1.collectible = false;
    std::shared_ptr<Object> obj3 = std::make_shared<Object>(t3, sf::Vector2f(
            800,
            300
    ), test1);

    this->objects.push_front(obj1);
    this->objects.push_front(obj2);
    this->objects.push_front(obj3);
}