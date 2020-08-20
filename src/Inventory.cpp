//
// Created by mattia on 19/05/20.
//

#include "Inventory.hpp"

Inventory::Inventory() {
    ObjectProperties test1;
    test1.id = 1;
    std::shared_ptr<Object> obj1 = std::make_shared<Object>(nullptr, sf::Vector2f(
            0,
            0
    ),test1);
    std::shared_ptr<Object> obj2 = std::make_shared<Object>(nullptr, sf::Vector2f(
            0,
            0
    ),test1);
    std::shared_ptr<Object> obj3 = std::make_shared<Object>(nullptr, sf::Vector2f(
            0,
            0
    ),test1);
    this->addObject(obj1);
    obj2->properties.id = 2;
    this->addObject(obj2);
    obj3->properties.id = 3;
    this->addObject(obj3);


}


void Inventory::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::RectangleShape liferect({static_cast<float>(50),150});
    liferect.setFillColor(sf::Color(200,200,0));
    liferect.setPosition( target.getView().getCenter().x + 345,target.getView().getCenter().y - 275);
    target.draw(liferect);
}

std::forward_list<std::shared_ptr<Object>> Inventory::getInventory() {
    return std::forward_list<std::shared_ptr<Object>>(this->inventory);
}

bool Inventory::addObject(std::shared_ptr<Object> obj) {
    this->inventory.push_front(obj);
}