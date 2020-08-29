//
// Created by vivedo on 11/05/20.
//

#ifndef STEALTH_OBJECT_HPP
#define STEALTH_OBJECT_HPP

#include "cfg.hpp"
#include <SFML/Graphics.hpp>
#include <utility>
#include "Tile.hpp"
#include "GameObject.hpp"

struct ObjectProperties {
    bool destroyable;
    bool explosive;
    bool collectible;
    int id;
};

class Object : public GameObject {
public:
    Object(std::shared_ptr<Tile> tile, sf::Vector2f position, ObjectProperties properties);
    Object(std::shared_ptr<Object> obj);
    Object(std::shared_ptr<Tile> tile, sf::Vector2f position): Object(std::move(tile), position, {false, false}) {};
    void setHealth(int health) const;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    ObjectProperties properties;
};


#endif //STEALTH_OBJECT_HPP
