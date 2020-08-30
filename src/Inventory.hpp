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
    void update();
    void releaseObject(int inventoryNumber);
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    std::forward_list<std::shared_ptr<Object>> inventory;
    sf::Vector2f firstItemPos;
    sf::Vector2f secondItemPos;
    sf::Vector2f thirdItemPos;
};


#endif //STEALTH_INVENTORY_HPP
