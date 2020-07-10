//
// Created by vivedo on 09/05/20.
//

#ifndef STEALTH_GAMEOBJECT_HPP
#define STEALTH_GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>
#include "Tile.hpp"

class GameObject : public sf::Drawable, public sf::Transformable {
public:
    virtual ~GameObject() override {};
    sf::Vector2f position;

    sf::Vector2f getPos() const {
        return position;
    }

    void setPos(sf::Vector2f &pos) {
        position = pos;
    }

    int getHealth() const {
        return health;
    }

    void setHealth(int h) {
        health = h;
    }

// protected:
    // TODO: make tile private and add getters and setters
    Tile &tile;

private:
    int health = 100;


};


#endif //STEALTH_GAMEOBJECT_HPP
