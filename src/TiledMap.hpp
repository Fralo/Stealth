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
#include "TiledLayer.hpp"

namespace xml = tinyxml2;

class TiledMap : public sf::Drawable, public sf::Transformable {
public:
    std::list<TiledLayer*> backgroundLayers;
    std::list<TiledLayer*> foregroundLayers;

    sf::Drawable &background = *new DrawableLayerGroup(backgroundLayers);
    sf::Drawable &foreground = *new DrawableLayerGroup(foregroundLayers);

    TiledMap();

    sf::Vector2u getMapSize();

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    int tileWidth;
    int tileHeight;
    int mapHeight;
    int mapWidth;
    std::forward_list<sf::Texture*> tilesets;
    std::map<int, sf::Sprite*> tiles;

    void loadTiles(xml::XMLElement *map);
    void loadLayerGroup(xml::XMLElement *group, std::list<TiledLayer*> &layerList);
    TiledLayer * makeLayer(xml::XMLElement *layer);

    class DrawableLayerGroup : public sf::Drawable, public sf::Transformable {
    public:
        DrawableLayerGroup(std::list<TiledLayer*> &layerGroup) : layerGroup(layerGroup) {};
    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    private:
        const std::list<TiledLayer*> &layerGroup;
    };
};


#endif //STEALTH_TILEDMAP_HPP
