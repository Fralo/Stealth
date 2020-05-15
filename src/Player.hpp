//
// Created by vivedo on 11/05/20.
//

#ifndef STEALTH_PLAYER_HPP
#define STEALTH_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "Weapon.h"
#include "Game.hpp"

class Player : public GameObject {
public:
    Player(sf::Vector2i position, Weapon weapon);
    void update(Game &game) override;

    void setNextPos( sf::Vector2i next );
    bool move;
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    Weapon weapon;
    sf::Vector2i nextPos;
};


#endif //STEALTH_PLAYER_HPP
