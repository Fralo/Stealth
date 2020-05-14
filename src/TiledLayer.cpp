//
// Created by vivedo on 11/05/20.
//

#include "TiledLayer.hpp"

TiledLayer::TiledLayer(sf::Vector2u layerSize, sf::Vector2u mapTileSize) : layerSize(layerSize), mapTileSize(mapTileSize){

}

sf::Sprite *TiledLayer::getTileSprite(unsigned int col, unsigned int row) const {
    if(row >= layerSize.y || col >= layerSize.x)
        return nullptr;

    if(!tiles.contains(row))
        return nullptr;

    if(!tiles.at(row).contains(col))
        return nullptr;

    sf::Sprite *tile = tiles.at(row).at(col);
    sf::IntRect tileSize = tile->getTextureRect();
    tile->setPosition(sf::Vector2f(col * mapTileSize.x, row * mapTileSize.y - (tileSize.height - mapTileSize.y)));

    return tile;
}

bool TiledLayer::setTileSprite(unsigned int row, unsigned int col, sf::Sprite *sprite) {
    if(row >= layerSize.y || col >= layerSize.x)
        return false;

    tiles[row][col] = sprite;
    return true;
}

void TiledLayer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Sprite *tile;
    for(int row = 0; row < layerSize.y; row++)
        for(int col = 0; col < layerSize.x; col++) {
            if ((tile = getTileSprite(col, row)) != nullptr) {
                target.draw(*tile);
            }

            // TODO: remove debug grid
            sf::RectangleShape tileRect(sf::Vector2f(mapTileSize.x, mapTileSize.y));
            tileRect.setPosition(sf::Vector2f(col * mapTileSize.x, row * mapTileSize.y));
            tileRect.setFillColor(sf::Color::Transparent);
            tileRect.setOutlineColor(sf::Color::Red);
            tileRect.setOutlineThickness(.5);
            target.draw(tileRect);
        }
}