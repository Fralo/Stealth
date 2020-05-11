//
// Created by vivedo on 11/05/20.
//

#ifndef STEALTH_TILEDMAP_H
#define STEALTH_TILEDMAP_H

#include <SFML/Graphics.hpp>
#include <tinyxml2/tinyxml2.h>
#include <forward_list>
#include <iostream>

namespace xml = tinyxml2;

class TiledMap : public sf::Drawable, public sf::Transformable {
public:
    TiledMap();

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    std::forward_list<sf::Texture*> tilesets;
    std::map<int, sf::Sprite*> tiles;

};


#endif //STEALTH_TILEDMAP_H
