//
// Created by vivedo on 11/05/20.
//

#include "Object.hpp"

Object::Object(std::shared_ptr<Tile> tile, sf::Vector2f position, ObjectProperties properties) : properties(properties) {
    GameObject::tile = tile;
    GameObject::position = position;
}


void Object::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if(tile != nullptr) {
        tile->setPosition(position);
        target.draw(*tile);
    }
    int red = 0;
    int green = 0;
    int blue = 0;
    switch(this->properties.id) {
        case 1:
            green = 255;
            break;
        case 2:
            red = 255;
            break;
        case 3:
            blue = 255;
            break;
        default:
            break;
    }
    sf::RectangleShape liferect({40,40});
    liferect.setFillColor(sf::Color(red,green,blue));
    liferect.setPosition( target.getView().getCenter().x + 345,target.getView().getCenter().y - 275 + ((this->properties.id - 1) * 45));

    target.draw(liferect);

#ifdef STEALTH_GRAPHIC_DEBUG
    if(tile->collisionBox.height > 0 && tile->collisionBox.width > 0) {
        sf::RectangleShape cb(sf::Vector2f(tile->collisionBox.width, tile->collisionBox.height));
        cb.setPosition(position.x + tile->collisionBox.left, position.y + tile->collisionBox.top);
        cb.setFillColor(sf::Color(255, 127, 0, 127));
        target.draw(cb);
    }
#endif

}

void Object::setHealth(int health) const {
    if(properties.destroyable)
        setHealth(health);
}
