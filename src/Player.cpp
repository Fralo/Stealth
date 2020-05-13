//
// Created by vivedo on 11/05/20.
//

#include "Player.hpp"

void Player::update(Game &game) {

}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {

}

Player::Player(sf::Vector2i position, Weapon weapon) : weapon(weapon) {
    this->position = position;

    std::cout << "Created Player" << std::endl
              << "  Position " << std::endl
              << "     x: " << position.x << std::endl
              << "     y: " << position.y << std::endl
              << "  Weapon:" << std::endl
              << "     Rate:   " << weapon.rate << std::endl
              << "     Damage: " << weapon.damage << std::endl;
}
