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
    obj->properties.numberInInventory = this->getSize() + 1;
    if(obj->properties.numberInInventory > 3) //TODO farlo costante
        return false;
    this->inventory.push_front(std::move(obj));
    return true;
}

std::shared_ptr<Object> Inventory::releaseObject(int inventoryNumber) {
    std::shared_ptr<Object> toRemove = nullptr;
    for (std::shared_ptr<Object> &obj : this->inventory) {
        if (obj->properties.numberInInventory == inventoryNumber) {
            toRemove = std::move(obj);
            this->inventory.remove(obj);
            break;
        }
    }
    if (toRemove != nullptr) {
        int i = 0;
        for (std::shared_ptr<Object> &obj : this->inventory)
            obj->properties.numberInInventory = ++i;

    }
    return toRemove;
}

int Inventory::getSize() {
    auto beg = inventory.begin();
    auto end = inventory.end();
    return std::distance(beg, end);
}

void Inventory::update() {

}