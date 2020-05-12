//
// Created by vivedo on 09/05/20.
//

#include "Enemy.hpp"

Enemy::Enemy(sf::Vector2i position, float orientation, Weapon weapon, EnemyView view, Strategy *defaultStrategy)
        : orientation(orientation), defaultStrategy(defaultStrategy), weapon(weapon), view(view) {
    this->position = position;
    strategy = defaultStrategy;

    std::cout << "Created Enemy" << std::endl
            << "  Position " << std::endl
            << "     x: " << position.x << std::endl
            << "     y: " << position.y << std::endl
            << "     o: " << orientation << std::endl
            << "  Weapon:" << std::endl
            << "     Rate:   " << weapon.rate << std::endl
            << "     Damage: " << weapon.damage << std::endl
            << "  View: " << std::endl
            << "     Distance: " << view.distance << std::endl
            << "     Radius:   " << view.radius << std::endl
            << "     Swing:    " << view.swing << std::endl;
}

void Enemy::update(Game &game) {
    sf::Vector2f nextMoveDirection = strategy->getNextMove(*this, game);

}

void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::RectangleShape rect(sf::Vector2f(20, 20));
    rect.setFillColor(sf::Color(0xff, 0x0, 0x0));
    rect.setPosition(position.x, position.y);
    target.draw(rect);
}


