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
#include <memory>
#include <sstream>
#include "macro.h"
#include "TiledLayer.hpp"
#include "Object.hpp"
#include "BackgroundObject.hpp"
#include "Tile.hpp"
#include "Animation.hpp"

namespace xml = tinyxml2;

class TiledMap : public sf::Drawable, public sf::Transformable {
public:
    explicit TiledMap(const char *levelFile, std::list<std::shared_ptr<Object>> &objects);

    TiledMap() = delete;

    sf::Vector2u getMapActualSize() const;

    Animation &getAnimation(const std::string &tileset, const std::string &type);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    int mapTileWidth;
    int mapTileHeight;
    int mapHeight;
    int mapWidth;

    std::list<std::shared_ptr<Object>> &objects;
    std::map<std::string, std::map<std::string, Animation>> animations;

    /*
     * Spritesheets are cached in sf::Textures and referenced by Tiles' sf::Sprites
     */
    std::forward_list<std::shared_ptr<sf::Texture>> tilesets;

    /*
     * Tiles stored with TMX globalID, used by TMX Layers
     */
    std::map<int, std::shared_ptr<Tile>> tiles;

    /*
     * Background layers, stored in TiledLayer class, which can draw the layer to a sf::RenderTarget
     */
    std::list<std::shared_ptr<TiledLayer>> mapLayers;

    /*
     * Cache Background layers rendering them to a RenderTexture and storing it into a Sprite to draw it to sd::RenderWindow
     */
    sf::RenderTexture cachedBgTexture;
    sf::Sprite cachedBgSprite;

    void loadTiles(xml::XMLElement *map);

    void loadLayerGroup(xml::XMLElement &group, std::list<std::shared_ptr<TiledLayer>> &layerList);

    std::shared_ptr<TiledLayer> makeLayer(xml::XMLElement &layer);

    void loadObjectGroup(xml::XMLElement &group, std::list<std::shared_ptr<Object>> &objectList);

    std::shared_ptr<Object> makeObject(xml::XMLElement &xmlObject);
};


#endif //STEALTH_TILEDMAP_HPP
