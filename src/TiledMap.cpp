//
// Created by vivedo on 11/05/20.
//

#include "TiledMap.hpp"

/*
 * Deserializes TMX map
 */
TiledMap::TiledMap(const char *levelFile, std::list<std::shared_ptr<Object>> &objects) : objects(objects) {
    auto xml = std::make_unique<xml::XMLDocument>();
    xml::XMLError error = xml->LoadFile(levelFile);

    if (error != tinyxml2::XML_SUCCESS) {
        std::cout << "Error opening map TMX file" << std::endl;
        throw std::exception();
    } else
        std::cout << "Map TMX file opened" << std::endl;

    xml::XMLElement *map = xml->FirstChildElement("map");

    mapTileWidth = map->IntAttribute("tilewidth");
    mapTileHeight = map->IntAttribute("tileheight");
    mapWidth = map->IntAttribute("width");
    mapHeight = map->IntAttribute("height");

    loadTiles(map);

    /*
     * Load layer groups
     */
    for (xml::XMLElement *group = map->FirstChildElement("group");
         group != nullptr; group = group->NextSiblingElement("group"))
        if (std::strcmp(group->Attribute("name"), "background") == 0)
            loadLayerGroup(*group, mapLayers);

    /*
     * Load object group
     */
    for (xml::XMLElement *group = map->FirstChildElement("objectgroup");
         group != nullptr; group = group->NextSiblingElement("objectgroup"))
        if (std::strcmp(group->Attribute("name"), "objects") == 0)
            loadObjectGroup(*group, objects);

    /*
     * Render background to texture only once
     */
    cachedBgTexture.create(mapWidth * mapTileWidth, mapHeight * mapTileHeight);
    cachedBgTexture.clear();
    for (std::shared_ptr<TiledLayer> layer : mapLayers)
        cachedBgTexture.draw(*layer);
    cachedBgTexture.display();
    cachedBgSprite.setTexture(cachedBgTexture.getTexture());
}

/*
 * Loads, stores and crops Tiles from Textures
 */
void TiledMap::loadTiles(xml::XMLElement *map) {
    for (xml::XMLElement *tileset = map->FirstChildElement("tileset");
         tileset != nullptr; tileset = tileset->NextSiblingElement("tileset")) {
        xml::XMLElement *image = tileset->FirstChildElement("image");

        std::string imagePath = resource("maps/");
        imagePath += image->Attribute("source");

        /*
         * Loads and stores sf::Texture
         */
        auto imageTexture = std::make_shared<sf::Texture>();
        imageTexture->loadFromFile(imagePath);
        tilesets.push_front(imageTexture);

        int firstGlobalId = tileset->IntAttribute("firstgid");
        int tileCount = tileset->IntAttribute("tilecount");
        int columns = tileset->IntAttribute("columns");

        /*
         * Creates and stores Tiles given their id
         */
        for (int i = 0; i < tileCount; i++) {
            int row = i / columns;
            int col = i % columns;

            auto sprite = std::make_shared<Tile>();
            sprite->setTexture(*imageTexture);
            int layerTileWidth = tileset->IntAttribute("tilewidth");
            int layerTileHeight = tileset->IntAttribute("tileheight");
            sf::IntRect rect = {col * layerTileWidth, row * layerTileHeight, layerTileWidth, layerTileHeight};
            sprite->setTextureRect(rect);

            //std::cout << rect.left << ":" << rect.top << ":" << rect.width << ":" << rect.height << std::endl;

            tiles[firstGlobalId + i] = sprite;
        }

        /*
         * Adds optional details to tiles
         */
        for (xml::XMLElement *tileDef = tileset->FirstChildElement("tile");
             tileDef != nullptr; tileDef = tileDef->NextSiblingElement("tile")) {
            int tileDefId = tileDef->IntAttribute("id");

            // load cx and cbox if present
            xml::XMLElement *objGroup = tileDef->FirstChildElement("objectgroup");
            if (objGroup)
                for (xml::XMLElement *object = objGroup->FirstChildElement("object");
                     object != nullptr; object = object->NextSiblingElement("object")) {
                    const char *objType = object->Attribute("type");

                    if (objType == nullptr)
                        continue;

                    if (!std::strcmp(objType, "cx")) { // object is center object
                        tiles[firstGlobalId + tileDefId]->drawingCenter = {
                                object->FloatAttribute("x"),
                                object->FloatAttribute("y")
                        };
                    } else if (!std::strcmp(objType, "cbox")) { // object is collision box
                        tiles[firstGlobalId + tileDefId]->collisionBox = {
                                object->FloatAttribute("x"),
                                object->FloatAttribute("y"),
                                object->FloatAttribute("width"),
                                object->FloatAttribute("height")
                        };
                    }
                }

            // load animation if present
            xml::XMLElement *animation = tileDef->FirstChildElement("animation");
            if (animation)
                for (xml::XMLElement *frame = animation->FirstChildElement("frame");
                     frame != nullptr; frame = frame->NextSiblingElement("frame")) {

                    const char *tileSetName = tileset->Attribute("name");
                    const char *animationName = tileDef->Attribute("type");

                    if (tileSetName != nullptr && animationName != nullptr)
                        animations[tileSetName][animationName].addFrame(
                                tiles[firstGlobalId + frame->IntAttribute("tileid")]);
                }
        }
    }
}

void TiledMap::loadLayerGroup(xml::XMLElement &group, std::list<std::shared_ptr<TiledLayer>> &layerList) {
    for (xml::XMLElement *layer = group.FirstChildElement("layer");
         layer != nullptr; layer = layer->NextSiblingElement("layer"))
        layerList.push_back(makeLayer(*layer));
}

std::shared_ptr<TiledLayer> TiledMap::makeLayer(xml::XMLElement &layer) {
    auto tiledLayer = std::make_shared<TiledLayer>(sf::Vector2u(mapWidth, mapHeight),
                                                   sf::Vector2u(mapTileWidth, mapTileHeight));

    std::stringstream data;
    data << layer.FirstChildElement("data")->GetText();

    // using a rough CSV parser, map is just a table of integers ids
    std::string line;
    for (int col = 0; std::getline(data, line) && col < mapHeight;) {
        std::stringstream lineStream;
        lineStream << line;

        if (line.empty()) // ignoring XML new lines
            continue;

        std::string tileStr;
        for (int row = 0; std::getline(lineStream, tileStr, ',') && row < mapWidth; row++) {
            int tileId = std::stoi(tileStr);
            if (tileId > 0) {// tileId == 0 means empty tile
                std::shared_ptr<Tile> tile = tiles.at(tileId);
                tiledLayer->setTileSprite(col, row, tile);

                if (tile->collisionBox.height > 0 && tile->collisionBox.width > 0)
                    objects.push_back(std::make_shared<BackgroundObject>(tile, sf::Vector2f(row * mapTileHeight,
                                                                                            col * mapTileWidth)));
            }
        }

        col++;
    }

    return tiledLayer;
}

void TiledMap::loadObjectGroup(xml::XMLElement &group, std::list<std::shared_ptr<Object>> &objectList) {
    for (xml::XMLElement *object = group.FirstChildElement("object");
         object != nullptr; object = object->NextSiblingElement("object"))
        objectList.push_back(makeObject(*object));
}

std::shared_ptr<Object> TiledMap::makeObject(xml::XMLElement &xmlObject) {
    int spriteId = xmlObject.IntAttribute("gid");

    xml::XMLElement *props = xmlObject.FirstChildElement("properties");

    ObjectProperties properties{};
    if(props != nullptr) {
        for(xml::XMLElement *property = props->FirstChildElement("property"); property != nullptr;
        property = property->NextSiblingElement("property")) {
            if(property->Attribute("name", "destroyable"))
                properties.destroyable = property->BoolAttribute("value", false);

            else if(property->Attribute("name", "explosive"))
                properties.explosive = property->BoolAttribute("value", false);

            else if(property->Attribute("name", "collectible"))
                properties.collectible = property->BoolAttribute("value", false);

            else if(property->Attribute("name", "explosionRadius"))
                properties.explosionRadius = property->IntAttribute("value", 0);

            else if(property->Attribute("name", "damage"))
                properties.damage = property->IntAttribute("value", 0);
        }
    }

    return std::make_shared<Object>(tiles[spriteId], sf::Vector2f(
            xmlObject.FloatAttribute("x"),
            xmlObject.FloatAttribute("y") - tiles[spriteId]->getTextureRect().height
    ), properties);
}

sf::Vector2u TiledMap::getMapActualSize() const {
    return sf::Vector2u(mapWidth * mapTileWidth, mapHeight * mapTileHeight);
}

void TiledMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(cachedBgSprite);
}

Animation &TiledMap::getAnimation(const std::string &tileset, const std::string &type) {
    if (animations.contains(tileset) && animations[tileset].contains(type))
        return animations[tileset][type];

    throw;
}
