//
// Created by vivedo on 14/05/20.
//

#include "Tile.hpp"

Tile::Tile() : drawingCenter(0, 0), collisionBox(0, 0, 0, 0) {}

Tile::Tile(sf::Vector2f drawingCenter, sf::FloatRect collisionBox) : drawingCenter(drawingCenter), collisionBox(collisionBox) {};