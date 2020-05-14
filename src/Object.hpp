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
    Object(Tile &tile, ObjectProperties properties);

    void update(Game &game) override;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:

    Tile &tile;
    ObjectProperties properties;
};


#endif //STEALTH_OBJECT_HPP
