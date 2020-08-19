//
// Created by mattia on 19/05/20.
//

#include "Inventory.hpp"

Inventory::Inventory() {
    InventoryItem item1;
    item1.id = 1;
    InventoryItem item2;
    item2.id = 2;
    InventoryItem item3;
    item3.id = 3;
    this->inventory.push_front(item1);
    this->inventory.push_front(item2);
    this->inventory.push_front(item3);
}


void Inventory::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::RectangleShape liferect({static_cast<float>(50),150});
    liferect.setFillColor(sf::Color(200,200,0));
    liferect.setPosition( target.getView().getCenter().x + 345,target.getView().getCenter().y - 275);
    target.draw(liferect);

    for(InventoryItem i : inventory) {
        int red = 0;
        int green = 0;
        int blue = 0;
        switch(i.id) {
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
        liferect.setPosition( target.getView().getCenter().x + 345,target.getView().getCenter().y - 275 + ((i.id - 1) * 45));

        target.draw(liferect);
    }
}
