//
// Created by vivedo on 09/05/20.
//

#ifndef STEALTH_GAMEOBJECT_HPP
#define STEALTH_GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>

class Game;

class GameObject : public sf::Drawable, public sf::Transformable {
public:
    virtual void update(Game &game) = 0;
    sf::Vector2f position;
};


#endif //STEALTH_GAMEOBJECT_HPP
