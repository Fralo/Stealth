//
// Created by vivedo on 11/05/20.
//

#include "Object.hpp"

#include <utility>
#include <iostream>

Object::Object(std::shared_ptr<Tile> tile, sf::Vector2f position, ObjectProperties properties, int health) : properties(
        properties), GameObject(std::move(tile), position) {
    setHealth(health);


#if defined(STEALTH_GRAPHIC_DEBUG) || defined(OBJECT_DEBUG)
    font.loadFromFile(resource("fonts/OpenSans-Regular.ttf"));
#endif
}

void Object::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (tile != nullptr) {
        if(this->properties.numberInInventory != 0) {
            tile->setPosition(target.getView().getCenter().x + centerDrawOffset,
                              target.getView().getCenter().y - centerDrawOffset + (properties.numberInInventory - 1) * distanceBetweenObj);
            tile->setScale(1.1,1.2);
        }
        else
            tile->setPosition(position);
        target.draw(*tile);
    }
    if (properties.destroyable) {
        //Draws HealthBar
        sf::RectangleShape re({static_cast<float>(getHealth()) / 100 * 20, 2});
        re.setPosition({getPos().x - 5, getPos().y - 5});
        re.setFillColor(sf::Color::Red);

        target.draw(re);
    }


#if defined(STEALTH_GRAPHIC_DEBUG) || defined(OBJECT_DEBUG)
    if(tile->collisionBox.height > 0 && tile->collisionBox.width > 0) {
        sf::RectangleShape cb(sf::Vector2f(tile->collisionBox.width, tile->collisionBox.height));
        cb.setPosition(position.x + tile->collisionBox.left, position.y + tile->collisionBox.top);
        cb.setFillColor(sf::Color(255, 127, 0, 127));
        target.draw(cb);
    }

    sf::Text txt;
    txt.setFont(font);
    std::stringstream coord;
    coord << "destroyable " << properties.destroyable << "\n"
            << "explosive " << properties.explosive << "\n"
            << "radius " << properties.explosionRadius << "\n"
            << "damage " << properties.damage << "\n"
            << "collectible " << properties.collectible << "\n";

    txt.setString(coord.str());
    txt.setPosition(position.x, position.y);
    txt.setScale(.3, .3);

    target.draw(txt);

#endif

}

bool Object::isDroppable(std::list<std::shared_ptr<Object>> &objects, sf::Vector2f playerPos) {
    for (auto &&obj : objects) {
        if (obj->properties.isTarget)
            continue;
        if (obj->getAbsCollisionBox().contains(playerPos.x + this->tile->collisionBox.width,
                                               playerPos.y + this->tile->collisionBox.height))
            return false;
    }
    return true;
}

void Object::applayDamage(int damage) {
    if (properties.destroyable)
        this->setHealth(health - damage > 0 ? health - damage : 0);
}

bool Object::explode(std::list<std::shared_ptr<Object>> &objects) {
    if (this->properties.explosive) {
        for (auto &&o : objects) {
            if (o->properties.isTarget &&
                MathHelper::distanceBetweenTwoPoints(o->getPos(), this->getPos()) < this->properties.explosionRadius) {
                o->applayDamage(this->properties.damage);
                std::cout<<o->getHealth()<<std::endl;
                return true;
            }
        }
    }
    return false;
}