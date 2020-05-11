//
// Created by vivedo on 11/05/20.
//

#include "TiledMap.h"

TiledMap::TiledMap() {
    xml::XMLDocument xml;
    xml::XMLError error = xml.LoadFile("../res/maps/01-map.tmx");

    if(error != tinyxml2::XML_SUCCESS){
        std::cout << "Error opening map TMX file" << std::endl;
        throw std::exception();
    } else
        std::cout << "TMX map file opened" << std::endl;

    xml::XMLElement *map = xml.FirstChildElement("map");

    for(xml::XMLElement *tileset = map->FirstChildElement("tileset"); tileset != nullptr; tileset = tileset->NextSiblingElement("tileset")) {
        xml::XMLElement *image = tileset->FirstChildElement("image");

        std::string imagePath = "../res/maps/";
        imagePath += image->Attribute("source");

        sf::Texture imageTexture;
        imageTexture.loadFromFile(imagePath);
        tilesets.push_front(&imageTexture);

        int firstGlobalId = std::stoi(tileset->Attribute("firstgid"));
        int tileWidth = std::stoi(tileset->Attribute("tilewidth"));
        int tileHeight = std::stoi(tileset->Attribute("tileheight"));
        int tileCount = std::stoi(tileset->Attribute("tilecount"));
        int columns = std::stoi(tileset->Attribute("columns"));

        for(int i = 0; i < tileCount; i++) {
            int col = i / columns;
            int row = i % columns;

            sf::Sprite sprite;
            sprite.setTexture(imageTexture);
            sf::IntRect rect = {col * tileWidth, row * tileHeight, tileWidth, tileHeight};
            sprite.setTextureRect(rect);

            tiles[firstGlobalId + i] = &sprite;
        }

    }
}

void TiledMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {

}


