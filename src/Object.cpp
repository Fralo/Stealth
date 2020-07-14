//
// Created by vivedo on 11/05/20.
//

#include "Object.hpp"

Object::Object(Tile &tile, sf::Vector2f position, ObjectProperties properties) : position(position), properties(properties) {
    GameObject::tile = &tile;
}


void Object::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    tile->setPosition(position);
    target.draw(*tile);

#ifdef STEALTH_GRAPHIC_DEBUG
    if(tile->collisionBox.height > 0 && tile->collisionBox.width > 0) {
        sf::RectangleShape cb(sf::Vector2f(tile->collisionBox.width, tile->collisionBox.height));
        cb.setPosition(position.x + tile->collisionBox.left, position.y + tile->collisionBox.top);
        cb.setFillColor(sf::Color(255, 127, 0, 127));
        target.draw(cb);
    }
#endif

}

void Object::setHealth(int health) const {
    if(properties.destroyable)
        setHealth(health);
}
