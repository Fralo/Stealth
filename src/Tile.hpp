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

    /*
     * Object center offset from tile position
     */
    sf::Vector2f drawingCenter = {0, 0};

    /*
     * Object collision box with offset from tile position
     */
    sf::FloatRect collisionBox = {0, 0, 0, 0};
};


#endif //STEALTH_TILE_HPP
