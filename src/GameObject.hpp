//
// Created by vivedo on 09/05/20.
//

#ifndef STEALTH_GAMEOBJECT_HPP
#define STEALTH_GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>

class GameObject {
public:
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow window) = 0;
};


#endif //STEALTH_GAMEOBJECT_HPP
