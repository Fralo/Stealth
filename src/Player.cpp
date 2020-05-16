//
// Created by vivedo on 11/05/20.
//

#include "Player.hpp"

void Player::update(Game &game) {

}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::CircleShape enemyShape(10);
    enemyShape.setFillColor(sf::Color(200, 0, 0));
    enemyShape.setPosition(position.x, position.y);
    target.draw(enemyShape);
}

Player::Player(sf::Vector2f position, Weapon weapon) : weapon(weapon) {
    this->position = position;

    std::cout << "Created Player" << std::endl
              << "  Position " << std::endl
              << "     x: " << position.x << std::endl
              << "     y: " << position.y << std::endl
              << "  Weapon:" << std::endl
              << "     Rate:   " << weapon.rate << std::endl
              << "     Damage: " << weapon.damage << std::endl;
}
