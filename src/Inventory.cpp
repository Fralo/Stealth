//
// Created by mattia on 19/05/20.
//

#include "Inventory.hpp"

Inventory::Inventory() {

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
    this->inventory.push_front(std::make_shared<Object>(obj));
    return true;
}

void Inventory::update() {
    firstItemPos.x = 100;
    firstItemPos.y = 100;
    std::forward_list<std::shared_ptr<Object>>::iterator it = inventory.begin();
    (**it).setPosition(firstItemPos);
}