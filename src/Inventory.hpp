//
// Created by mattia on 19/05/20.
//

#ifndef STEALTH_INVENTORY_H
#define STEALTH_INVENTORY_H


#include <SFML/Graphics.hpp>
#include <forward_list>
#include <memory>
#include "Tile.hpp"
#include <iostream>
#include "Object.hpp"

class Inventory : public sf::Drawable, public sf::Transformable {
public:
    Inventory();

    std::forward_list<std::shared_ptr<Object>> getInventory();

    bool addObject(std::shared_ptr<Object> obj);

    std::shared_ptr<Object>
    releaseObject(int inventoryNumber, std::list<std::shared_ptr<Object>> &objects, sf::Vector2f playerPos);

    void update();

    int getSize();

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    std::forward_list<std::shared_ptr<Object>> inventory;
    const int maxInventorySize = 3;
};


#endif //STEALTH_INVENTORY_HPP
