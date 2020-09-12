//
// Created by mattia on 19/05/20.
//

#include "Inventory.hpp"

Inventory::Inventory() {
    inventoryTexture.loadFromFile(resource("inventory.png"));
}


void Inventory::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Sprite inventorySprite;
    inventorySprite.setTexture(inventoryTexture);

    inventorySprite.setTextureRect(sf::IntRect(0,0, 130,350));
    inventorySprite.setPosition(target.getView().getCenter().x + 330,
                                                 target.getView().getCenter().y - 375);
    inventorySprite.setScale(sf::Vector2f(0.5, 0.5));
    target.draw(inventorySprite);
}

std::forward_list<std::shared_ptr<Object>> Inventory::getInventory() {
    return std::forward_list<std::shared_ptr<Object>>(this->inventory);
}

bool Inventory::addObject(std::shared_ptr<Object> obj) {
    obj->properties.numberInInventory = this->getSize() + 1;
    if (obj->properties.numberInInventory > maxInventorySize)
        return false;
    this->inventory.push_front(std::move(obj));
    return true;
}

std::shared_ptr<Object>
Inventory::releaseObject(int inventoryNumber, std::list<std::shared_ptr<Object>> &objects, sf::Vector2f playerPos) {
    std::shared_ptr<Object> toRemove = nullptr;
    for (std::shared_ptr<Object> &obj : this->inventory) {
        if (obj->properties.numberInInventory == inventoryNumber && obj->isDroppable(objects, playerPos)) {
            toRemove = std::move(obj);
            this->inventory.remove(obj);
            break;
        }
    }
    //riassegno gli indici all'inventario
    if (toRemove != nullptr) {
        int i = 0;
        for (std::shared_ptr<Object> &obj : this->inventory)
            obj->properties.numberInInventory = ++i;

        toRemove->properties.numberInInventory = 0;
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
