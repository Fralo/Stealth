//
// Created by vivedo on 11/05/20.
//

#include "TiledMap.hpp"

/*
 * Deserializes TMX map
 */
TiledMap::TiledMap(std::list<Object*> &objects) : objects(objects) {
    xml::XMLDocument xml;
    xml::XMLError error = xml.LoadFile(resource("maps/01-map.tmx")); // TODO: get map from constructor

    if(error != tinyxml2::XML_SUCCESS){
        std::cout << "Error opening map TMX file" << std::endl;
        throw std::exception();
    } else
        std::cout << "Map TMX file opened" << std::endl;

    xml::XMLElement *map = xml.FirstChildElement("map");

    mapTileWidth = map->IntAttribute("tilewidth");
    mapTileHeight = map->IntAttribute("tileheight");
    mapWidth = map->IntAttribute("width");
    mapHeight = map->IntAttribute("height");

    loadTiles(map);

    for(xml::XMLElement *group = map->FirstChildElement("group"); group != nullptr; group = group->NextSiblingElement("group"))
        if(std::strcmp(group->Attribute("name"), "background") == 0)
            loadLayerGroup(*group, mapLayers);
        else if(std::strcmp(group->Attribute("name"), "objects") == 0)
            loadObjectGroup(*group, objects);
}

/*
 * Loads, stores and crops Tiles from Textures
 */
void TiledMap::loadTiles(xml::XMLElement *map) {
    for(xml::XMLElement *tileset = map->FirstChildElement("tileset"); tileset != nullptr; tileset = tileset->NextSiblingElement("tileset")) {
        xml::XMLElement *image = tileset->FirstChildElement("image");

        std::string imagePath = resource("maps/");
        imagePath += image->Attribute("source");

        /*
         * Loads and stores sf::Texture
         */
        auto *imageTexture = new sf::Texture();
        imageTexture->loadFromFile(imagePath);
        tilesets.push_front(imageTexture);

        int firstGlobalId = tileset->IntAttribute("firstgid");
        int tileCount = tileset->IntAttribute("tilecount");
        int columns = tileset->IntAttribute("columns");

        /*
         * Creates and stores Tiles given their id
         */
        for(int i = 0; i < tileCount; i++) {
            int row = i / columns;
            int col = i % columns;

            auto *sprite = new Tile();
            sprite->setTexture(*imageTexture);
            int layerTileWidth = tileset->IntAttribute("tilewidth");
            int layerTileHeight = tileset->IntAttribute("tileheight");
            sf::IntRect rect = {col * layerTileWidth, row * layerTileHeight, layerTileWidth, layerTileHeight};
            sprite->setTextureRect(rect);

            std::cout << rect.left << ":" << rect.top << ":" << rect.width << ":" << rect.height << std::endl;

            tiles[firstGlobalId + i] = sprite;
        }

        /*
         * Adds optional details to tiles (mainly collision boxes for tiles used as objects)
         */
        for(xml::XMLElement *tileDef = tileset->FirstChildElement("tile"); tileDef != nullptr; tileDef = tileDef->NextSiblingElement("tile")) {
            int tileDefId = tileDef->IntAttribute("id");

            xml::XMLElement *objGroup = tileDef->FirstChildElement("objectgroup");
            for(xml::XMLElement *object = objGroup->FirstChildElement("object"); object != nullptr; object = object->NextSiblingElement("object")) {
                const char *objType = object->Attribute("type");

                if(objType == nullptr)
                    continue;

                if(!std::strcmp(objType, "cx")) { // object is center object
                    tiles[firstGlobalId + tileDefId]->drawingCenter = {
                            object->FloatAttribute("x"),
                            object->FloatAttribute("y")
                    };
                } else if(!std::strcmp(objType, "cbox")) { // object is collision box
                    tiles[firstGlobalId + tileDefId]->collisionBox = {
                            object->FloatAttribute("x"),
                            object->FloatAttribute("y"),
                            object->FloatAttribute("width"),
                            object->FloatAttribute("height")
                    };
                }
            }
        }
    }
}

void TiledMap::loadLayerGroup(xml::XMLElement &group, std::list<TiledLayer *> &layerList) {
    for(xml::XMLElement *layer = group.FirstChildElement("layer"); layer != nullptr; layer = layer->NextSiblingElement("layer"))
        layerList.push_back(makeLayer(*layer));
}

TiledLayer *TiledMap::makeLayer(xml::XMLElement &layer) {
    auto *tiledLayer = new TiledLayer(sf::Vector2u(mapWidth, mapHeight), sf::Vector2u(mapTileWidth, mapTileHeight));

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

void TiledMap::loadObjectGroup(xml::XMLElement &group, std::list<Object *> &objectList) {
    std::cout << "loadObjectGroup" << std::endl;
    for(xml::XMLElement *objectgroup = group.FirstChildElement("objectgroup"); objectgroup != nullptr; objectgroup = objectgroup->NextSiblingElement("objectgroup"))
        for(xml::XMLElement *object = objectgroup->FirstChildElement("object"); object != nullptr; object = object->NextSiblingElement("object"))
            objectList.push_back(makeObject(*object));
}

Object *TiledMap::makeObject(xml::XMLElement &xmlObject) {
    int spriteId = xmlObject.IntAttribute("gid");
    ObjectProperties properties = {
            xmlObject.BoolAttribute("destroyable", false),
            xmlObject.BoolAttribute("explosive", false)
    };

    auto *obj = new Object(*tiles[spriteId], properties);
    obj->position = {
            xmlObject.IntAttribute("x"),
            xmlObject.IntAttribute("y")
    };
    return obj;
}

sf::Vector2u TiledMap::getMapSize() const {
    return sf::Vector2u(mapWidth, mapHeight);
}

sf::Vector2u TiledMap::getTileSize() const {
    return sf::Vector2u(mapTileWidth, mapTileHeight);
}

sf::Vector2u TiledMap::getMapActualSize() const {
    return sf::Vector2u(mapWidth * mapTileWidth, mapHeight * mapTileHeight);
}

void TiledMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for(TiledLayer *layer : mapLayers)
        target.draw(*layer);

    std::cout << "objects: " << objects.size() << std::endl;

    // TODO: draw objects based on player y position
    for(Object *obj : objects)
        target.draw(*obj);
}