//
// Created by vivedo on 11/05/20.
//

#ifndef STEALTH_TILEDLAYER_HPP
#define STEALTH_TILEDLAYER_HPP


#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>

class TiledLayer : public sf::Drawable, public sf::Transformable {
public:
    TiledLayer(sf::Vector2u layerSize, sf::Vector2u tileSize);

    sf::Sprite * getTileSprite(unsigned int col, unsigned int row) const;
    bool setTileSprite(unsigned int col, unsigned int row, sf::Sprite *sprite);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    const sf::Vector2u tileSize;
    const sf::Vector2u layerSize;
    std::map<unsigned int, std::map<unsigned int, sf::Sprite*>> tiles;
};


#endif //STEALTH_TILEDLAYER_HPP
