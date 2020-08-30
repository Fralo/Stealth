//
// Created by mattia on 19/05/20.
//

#include "Inventory.hpp"

Inventory::Inventory() {

}


void Inventory::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::RectangleShape rect({static_cast<float>(50),150});
    rect.setFillColor(sf::Color(200,200,0));
    rect.setPosition( target.getView().getCenter().x + 345,target.getView().getCenter().y - 375);
    target.draw(rect);
}

std::forward_list<std::shared_ptr<Object>> Inventory::getInventory() {
    return std::forward_list<std::shared_ptr<Object>>(this->inventory);
}

bool Inventory::addObject(std::shared_ptr<Object> obj) {
    //TODO insert in the right order;
    obj->properties.numberInInventory = 
    this->inventory.push_front(std::make_shared<Object>(obj));
    return true;
}

void Inventory::update() {

}