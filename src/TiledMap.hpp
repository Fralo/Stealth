//
// Created by vivedo on 11/05/20.
//

#ifndef STEALTH_TILEDMAP_HPP
#define STEALTH_TILEDMAP_HPP

#include <SFML/Graphics.hpp>
#include <tinyxml2/tinyxml2.h>
#include <forward_list>
#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include "macro.h"
#include "TiledLayer.hpp"
#include "Object.hpp"
#include "Tile.hpp"

namespace xml = tinyxml2;

class TiledMap : public sf::Drawable, public sf::Transformable {
public:
    TiledMap(std::list<Object*> &objects);
    TiledMap() = delete;

    std::list<TiledLayer*> mapLayers;
    std::list<Object*> &objects;
    sf::Vector2u getMapSize() const;
    sf::Vector2u getTileSize() const;
    sf::Vector2u getMapActualSize() const;
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    int mapTileWidth;
    int mapTileHeight;
    int mapHeight;
    int mapWidth;
    std::forward_list<sf::Texture*> tilesets;
    std::map<int, Tile*> tiles;

    void loadTiles(xml::XMLElement *map);
    void loadLayerGroup(xml::XMLElement &group, std::list<TiledLayer*> &layerList);
    TiledLayer *makeLayer(xml::XMLElement &layer);
    void loadObjectGroup(xml::XMLElement &group, std::list<Object*> &objectList);
    Object *makeObject(xml::XMLElement &xmlObject);
};


#endif //STEALTH_TILEDMAP_HPP
