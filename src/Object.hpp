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
struct ObjectProperties {
    bool destroyable;
    bool explosive;
    bool collectible;
    int id;
    int numberInInventory; //if is not equal to 0, it means that the object is collected in the inventory and indicate the position that should have in the inventory and the key to press to be released
    int explosionRadius;
    int damage;
};

class Object : public GameObject {
public:
    Object(std::shared_ptr<Tile> tile, sf::Vector2f position, ObjectProperties properties);
    Object(std::shared_ptr<Object> obj);
    Object(std::shared_ptr<Tile> tile, sf::Vector2f position): Object(std::move(tile), position, {false, false}) {};
    bool isDroppable( std::list<std::shared_ptr<Object>>& objects, sf::Vector2f playerPos );
    bool explode(std::list<std::shared_ptr<Object>>& objects);
    void applayDamage(int damage);
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    ObjectProperties properties;

};


#endif //STEALTH_OBJECT_HPP
