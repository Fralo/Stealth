//
// Created by vivedo on 18/07/20.
//

#include "GameObject.hpp"

GameObject::GameObject(std::shared_ptr<Tile> tile, sf::Vector2f position) : tile(std::move(tile)), position(position) {}

sf::Vector2f GameObject::getPos() const {
    return position;
}

void GameObject::setPos(sf::Vector2f pos) {
    position = pos;
}

void GameObject::setPos(int x, int y) {
    position.x = x;
    position.y = y;
}

int GameObject::getHealth() const {
    return health;
}

void GameObject::setHealth(int h) {
    health = h < 0 ? 0 : h;
}

sf::Vector2f GameObject::getAbsDrawingCenter() {
    if (tile != nullptr)
        return position + tile->drawingCenter;
    return position;
}

sf::FloatRect GameObject::getAbsCollisionBox() {
    //TODO remove this sh*t
    return sf::FloatRect({tile->collisionBox.left + position.x, tile->collisionBox.top + position.y,
                          tile->collisionBox.width, tile->collisionBox.height});
}

