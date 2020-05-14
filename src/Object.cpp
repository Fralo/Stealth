//
// Created by vivedo on 11/05/20.
//

#include "Object.hpp"

Object::Object(Tile &tile, ObjectProperties properties) : tile(tile), properties(properties) {}

void Object::update(Game &game) {

}

void Object::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(tile);
}
