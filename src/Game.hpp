//
// Created by vivedo on 09/05/20.
//

#ifndef STEALTH_GAME_HPP
#define STEALTH_GAME_HPP

#include <SFML/Graphics.hpp>
#include <tinyxml2/tinyxml2.h>
#include <algorithm>
#include <iostream>
#include "cfg.hpp"
#include "GameState.hpp"
#include "Stealth.hpp"
#include "TiledMap.hpp"
#include "GameObject.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Object.hpp"
#include "SeekStrategy.hpp"
#include "GameCursor.hpp"

class Player;
class Enemy;

namespace xml = tinyxml2;

/*
 * TICKDELAY = 1000ms / tickrate
 */
#define TICKDELAY 20

class Game : public GameState {
public:
    void init(Stealth &stealth) override;
    void update(Stealth &stealth) override;

protected:
    void handleEvent(Stealth &stealth, sf::Event &event) override;

private:
    std::forward_list<std::shared_ptr<Enemy>> enemies;
    std::list<std::shared_ptr<Object>> objects;
    std::shared_ptr<Player> player;
    std::shared_ptr<TiledMap> map;
    GameCursor cursor;
    sf::View view;
    sf::Clock clock;

    sf::Clock tickClock;

    sf::Music levelMusic;

    void loadMapConfig();
    void loadEnemies(xml::XMLElement *root);
    void updateMapView(Stealth &stealth);

};


#endif //STEALTH_GAME_HPP
