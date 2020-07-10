//
// Created by vivedo on 11/05/20.
//

#ifndef STEALTH_OBJECT_HPP
#define STEALTH_OBJECT_HPP

#include <SFML/Graphics.hpp>
#include "Tile.hpp"
#include "GameObject.hpp"

struct ObjectProperties {
    bool destroyable;
    bool explosive;
};

class Object : public GameObject {
public:
    Object(Tile &tile, sf::Vector2f position, ObjectProperties properties);
    void setHealth(int health) const ;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    sf::Vector2f position;
    Tile &tile;
    ObjectProperties properties;
};


#endif //STEALTH_OBJECT_HPP
