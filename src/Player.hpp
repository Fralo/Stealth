//
// Created by vivedo on 11/05/20.
//

#ifndef STEALTH_PLAYER_HPP
#define STEALTH_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "Weapon.h"
#include "Game.hpp"
#include "Astar.hpp"

#define GRID_SCALE_FACTOR 16

class Player : public GameObject {
public:
    Player(sf::Vector2f position, Weapon weapon);
    void update(Game &game) override;

    void setNextPos(sf::Vector2f next);
    bool move;
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    Weapon weapon;
    sf::Vector2f nextPos;
    sf::Clock cacheTime;
    Path *path = nullptr;

    sf::SoundBuffer movingSfxBuffer;
    sf::Sound movingSfx;
};


#endif //STEALTH_PLAYER_HPP
