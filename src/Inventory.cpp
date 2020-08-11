//
// Created by mattia on 19/05/20.
//

#include "Inventory.hpp"



void Inventory::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::RectangleShape liferect({static_cast<float>(40),200});
    liferect.setFillColor(sf::Color(200,200,0));
    liferect.setPosition( target.getView().getCenter().x + 350,target.getView().getCenter().y - 250);
    target.draw(liferect);
}
