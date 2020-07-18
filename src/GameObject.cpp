//
// Created by vivedo on 18/07/20.
//

#include "GameObject.hpp"

sf::Vector2f GameObject::getPos() const {
    return position;
}

void GameObject::setPos(sf::Vector2f pos) {
    position = pos;
}

int GameObject::getHealth() const {
    return health;
}

void GameObject::setHealth(int h) {
    health = h;
}

sf::Vector2f GameObject::getAbsDrawingCenter() {
    if(tile != nullptr)
        return position + tile->drawingCenter;
    return position;
}

sf::FloatRect GameObject::getAbsCollisionBox() {
    return sf::FloatRect({tile->collisionBox.left + position.x, tile->collisionBox.top + position.y,
                          tile->collisionBox.width, tile->collisionBox.height});
}

