//
// Created by mattia on 08/09/20.
//

#include "GameTest.hpp"

void GameTest::init() {
    killedEnemyObserver = std::make_shared<KilledEnemyObserver>();
    stealthStatusObserver = std::make_shared<StealthStatusObserver>();

    map = std::make_shared<TiledMap>(resource("maps/02-map.tmx"), objects);
    loadMapConfig();
    inventory = std::make_shared<Inventory>();
    gameViewClock.restart();

}

void GameTest::simulateClickOnEnemy() {
    for(std::shared_ptr<Enemy> e : enemies)
        if(e->getPos().x == 100 && e->getPos().y == 400)
             player->shootEnemy(e);
}

int GameTest::getEnemiesNumber() {
    return std::distance(enemies.begin(),enemies.end());
}

void GameTest::update() {
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

    /*
     * Check player life
     */

    if(player->getHealth() == 0)
    {

    }

    /*
     * Check enemy life
     */
    for(const std::shared_ptr<Enemy> &e : enemies) {
        if (e->getHealth() == 0) {
            std::cout<<"Hello"<<std::endl;
            enemies.remove(e);
            break;
        }
    }
    /*
     * Check target object life
     */
    for (auto &&o : this->objects)
        if (o->properties.id == 1 && o->getHealth() == 0)
        {

        }

    /*
     * Draw objects
     */

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

}


