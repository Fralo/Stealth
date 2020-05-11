//
// Created by vivedo on 09/05/20.
//

#ifndef STEALTH_GAME_HPP
#define STEALTH_GAME_HPP


#include <SFML/Graphics.hpp>
#include <tinyxml2/tinyxml2.h>
#include <iostream>
#include "GameState.hpp"
#include "Stealth.hpp"
#include "TiledMap.h"
#include "GameObject.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

class Player;
class Enemy;

namespace xml = tinyxml2;

class Game : public GameState {
public:
    void init(Stealth &stealth) override;

    void update(Stealth &stealth) override;

    std::forward_list<Enemy*> enemies;
    Player *player;

protected:
    void handleEvent(Stealth &stealth, sf::Event &event) override;

private:
    void loadMap();
};


#endif //STEALTH_GAME_HPP
