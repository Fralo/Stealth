//
// Created by vivedo on 09/05/20.
//

#ifndef STEALTH_GAMEOBJECT_HPP
#define STEALTH_GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>

class GameObject : public sf::Drawable, public sf::Transformable {
public:
    virtual ~GameObject() override {};
    sf::Vector2f position;

    const sf::Vector2f &getPosition1() const {
        return position;
    }

    void setPosition1(const sf::Vector2f &position) {
        GameObject::position = position;
    }

    int getHealth() const {
        return health;
    }

    void setHealth(int health) {
        GameObject::health = health;
    }

private:
    int health = 100;


};


#endif //STEALTH_GAMEOBJECT_HPP
