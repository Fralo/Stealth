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
#include "MathHelper.hpp"
#include <list>
#include <sstream>
#include "macro.h"

// #define OBJECT_DEBUG

struct ObjectProperties {
    bool destroyable;
    bool explosive;
    bool collectible;
    bool isTarget;
    int explosionRadius;
    int damage;
    int id;
    int numberInInventory; //if is not equal to 0, it means that the object is collected in the inventory and indicate the position that should have in the inventory and the key to press to be released
};

class Object : public GameObject {
public:
    Object(std::shared_ptr<Tile> tile, sf::Vector2f position, ObjectProperties properties, int health);

    Object(std::shared_ptr<Tile> tile, sf::Vector2f position) : Object(std::move(tile), position, {}, 100) {};

    bool isDroppable(std::list<std::shared_ptr<Object>> &objects, sf::Vector2f playerPos);

    bool explode(std::list<std::shared_ptr<Object>> &objects);

    void applayDamage(int damage);

    ObjectProperties properties;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
#if defined(STEALTH_GRAPHIC_DEBUG) || defined(OBJECT_DEBUG)
    sf::Font font;
#endif

};


#endif //STEALTH_OBJECT_HPP
