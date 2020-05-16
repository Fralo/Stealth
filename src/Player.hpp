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
    Player(sf::Vector2f position, Weapon weapon);
    void update(Game &game) override;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    Weapon weapon;
};


#endif //STEALTH_PLAYER_HPP
