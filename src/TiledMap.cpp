//
// Created by vivedo on 11/05/20.
//

#include "TiledMap.hpp"

TiledMap::TiledMap(std::forward_list<Obstacle*> &obstacles) {
    xml::XMLDocument xml;
    xml::XMLError error = xml.LoadFile(resource("maps/01-map.tmx")); // TODO: get map from constructor

    if(error != tinyxml2::XML_SUCCESS){
        std::cout << "Error opening map TMX file" << std::endl;
        throw std::exception();
    } else
        std::cout << "Map TMX file opened" << std::endl;

    xml::XMLElement *map = xml.FirstChildElement("map");

    tileWidth = map->IntAttribute("tilewidth");
    tileHeight = map->IntAttribute("tileheight");
    mapWidth = map->IntAttribute("width");
    mapHeight = map->IntAttribute("height");

    loadTiles(map);

    for(xml::XMLElement *group = map->FirstChildElement("group"); group != nullptr; group = group->NextSiblingElement("group"))
        if(std::strcmp(group->Attribute("name"), "background") == 0)
            loadLayerGroup(*group, backgroundLayers);
        else if(std::strcmp(group->Attribute("name"), "foreground") == 0) { // TODO: rename foreground layer into obstacles
            loadLayerGroup(*group, foregroundLayers);

        }

}

void TiledMap::loadTiles(xml::XMLElement *map) {
    for(xml::XMLElement *tileset = map->FirstChildElement("tileset"); tileset != nullptr; tileset = tileset->NextSiblingElement("tileset")) {
        xml::XMLElement *image = tileset->FirstChildElement("image");

        std::string imagePath = resource("maps/");
        imagePath += image->Attribute("source");

        auto *imageTexture = new sf::Texture();
        imageTexture->loadFromFile(imagePath);
        tilesets.push_front(imageTexture);

        int firstGlobalId = tileset->IntAttribute("firstgid");
        int tileCount = tileset->IntAttribute("tilecount");
        int columns = tileset->IntAttribute("columns");

        for(int i = 0; i < tileCount; i++) {
            int row = i / columns;
            int col = i % columns;

            auto *sprite = new sf::Sprite();
            sprite->setTexture(*imageTexture);
            sf::IntRect rect = {col * tileWidth, row * tileHeight, tileWidth, tileHeight};
            sprite->setTextureRect(rect);

            tiles[firstGlobalId + i] = sprite;
        }
    }
}

void TiledMap::loadLayerGroup(xml::XMLElement &group, std::list<TiledLayer *> &layerList) {
    for(xml::XMLElement *layer = group.FirstChildElement("layer"); layer != nullptr; layer = layer->NextSiblingElement("layer"))
        layerList.push_back(makeLayer(*layer));
}

TiledLayer *TiledMap::makeLayer(xml::XMLElement &layer) {
    auto *tiledLayer = new TiledLayer(sf::Vector2u(mapWidth, mapHeight), sf::Vector2u(tileWidth, tileHeight));

    std::stringstream data;
    data << layer.FirstChildElement("data")->GetText();

    // using a rough CSV parser, map is just a collection of integers ids

    std::string line;
    for(int col = 0; std::getline(data, line) && col < mapHeight;) {
        std::stringstream lineStream;
        lineStream << line;

        if(line.empty()) // ignoring XML new lines
            continue;

        std::string tile;
        for(int row = 0; std::getline(lineStream, tile, ',') && row < mapWidth; row++) {

            int tileId = std::stoi(tile);
            if(tileId > 0) // tileId == 0 means empty tile
                tiledLayer->setTileSprite(col, row, tiles.at(tileId));
        }

        col++; // increment col only if line is valid
    }

    return tiledLayer;
}

sf::Vector2u TiledMap::getMapSize() const {
    return sf::Vector2u(mapWidth, mapHeight);
}

sf::Vector2u TiledMap::getTileSize() const {
    return sf::Vector2u(tileWidth, tileHeight);
}

sf::Vector2u TiledMap::getMapActualSize() const {
    return sf::Vector2u(mapWidth * tileWidth, mapHeight * tileHeight);
}

void TiledMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(background);
    target.draw(foreground);
}

void TiledMap::DrawableLayerGroup::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for(TiledLayer *layer : layerGroup)
        target.draw(*layer);
}
