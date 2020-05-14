//
// Created by vivedo on 14/05/20.
//

#ifndef STEALTH_TILE_HPP
#define STEALTH_TILE_HPP

#include <SFML/Graphics.hpp>

class Tile : public sf::Sprite {
public:
    Tile();
    Tile(sf::Vector2f drawingCenter, sf::FloatRect collisionBox);

    sf::Vector2f drawingCenter;
    sf::FloatRect collisionBox;
};


#endif //STEALTH_TILE_HPP
