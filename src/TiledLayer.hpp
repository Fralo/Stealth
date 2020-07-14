//
// Created by vivedo on 11/05/20.
//

#ifndef STEALTH_TILEDLAYER_HPP
#define STEALTH_TILEDLAYER_HPP


#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include <memory>
#include "macro.h"
#include <sstream>

class TiledLayer : public sf::Drawable, public sf::Transformable {
public:
    TiledLayer(sf::Vector2u layerSize, sf::Vector2u mapTileSize);

    std::shared_ptr<sf::Sprite> getTileSprite(unsigned int col, unsigned int row) const;
    bool setTileSprite(unsigned int col, unsigned int row, std::shared_ptr<sf::Sprite> sprite);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    const sf::Vector2u mapTileSize;
    const sf::Vector2u layerSize;
    std::map<unsigned int, std::map<unsigned int, std::shared_ptr<sf::Sprite>>> tiles;

    // TODO: debug only, remove
    sf::Font font;
};


#endif //STEALTH_TILEDLAYER_HPP
