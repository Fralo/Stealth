//
// Created by vivedo on 23/07/20.
//

#ifndef STEALTH_BACKGROUNDOBJECT_HPP
#define STEALTH_BACKGROUNDOBJECT_HPP

#include <memory>
#include <utility>
#include "Object.hpp"
#include "cfg.hpp"

class BackgroundObject : public Object {
public:
    BackgroundObject(std::shared_ptr<Tile> tile, sf::Vector2f position) : Object(std::move(tile), position) {};

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
#ifdef STEALTH_GRAPHIC_DEBUG
        if(tile->collisionBox.height > 0 && tile->collisionBox.width > 0) {
            sf::RectangleShape cb(sf::Vector2f(tile->collisionBox.width, tile->collisionBox.height));
            cb.setPosition(position.x + tile->collisionBox.left, position.y + tile->collisionBox.top);
            cb.setFillColor(sf::Color(255, 127, 0, 127));
            target.draw(cb);
        }
#endif
    };
};


#endif //STEALTH_BACKGROUNDOBJECT_HPP
