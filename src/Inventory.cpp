//
// Created by mattia on 19/05/20.
//

#include "Inventory.hpp"

Inventory::Inventory() {
    InventoryItem test;
    test.id = 12;
    this->inventory.push_front(test);
}


void Inventory::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::RectangleShape liferect({static_cast<float>(50),150});
    liferect.setFillColor(sf::Color(200,200,0));
    liferect.setPosition( target.getView().getCenter().x + 345,target.getView().getCenter().y - 275);
    target.draw(liferect);

    for(InventoryItem i : inventory) {
        sf::RectangleShape liferect({40,40});
        liferect.setFillColor(sf::Color(100,200,0));
        liferect.setPosition( target.getView().getCenter().x + 345,target.getView().getCenter().y - 275);
        target.draw(liferect);
        std::cout<<i.id<<std::endl;
    }
}
