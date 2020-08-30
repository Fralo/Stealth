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
#include "Inventory.hpp"
#include "AdvancementManager.hpp"
class AdvancementManager;

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
    AdvancementManager *advancementManager;
    std::forward_list<std::shared_ptr<Enemy>> enemies;
    std::list<std::shared_ptr<Object>> objects;
    std::shared_ptr<Player> player;
    std::shared_ptr<Inventory> inventory;
    std::shared_ptr<TiledMap> map;
    GameCursor cursor;
    sf::View gameView;
    sf::View guiView;
    sf::Clock gameViewClock;

    sf::Clock tickClock;

    sf::Music levelMusic;

    sf::SoundBuffer denyMoveSfxBuffer;
    sf::Sound denyMoveSfx;

    void loadMapConfig();
    void loadEnemies(xml::XMLElement *root);
    void loadObjects();
    void updateViews(Stealth &stealth);


};


#endif //STEALTH_GAME_HPP
