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
            << "     Angle:    " << view.angle << std::endl
            << "     Swing:    " << view.swing << std::endl;
}

void Enemy::update(Game &game) {
    //sf::Vector2f nextMoveDirection = strategy->getNextMove(*this, game);

    sightSwingVariation = view.swing * std::sin(clock.getElapsedTime().asMilliseconds() / 1000.0f);
}

void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::CircleShape enemyShape(10);
    enemyShape.setFillColor(sf::Color(100, 250, 50));
    enemyShape.setPosition(position.x - 10, position.y - 10);
    target.draw(enemyShape);

    sf::ConvexShape sightTriangle = getSightTraigle();
    sightTriangle.setFillColor(sf::Color(0x0, 0xd0, 0x20, 0x7f));

    target.draw(sightTriangle);
}

sf::ConvexShape Enemy::getSightTraigle() const {
    sf::ConvexShape triangle(3);
    triangle.setPoint(0, sf::Vector2f(0, 0));

    float radius = view.distance / std::cos(M_PI * view.angle / 2);

    sf::Vector2f A(radius * std::cos((-orientation + sightSwingVariation - view.angle) * M_PI), radius * std::sin((-orientation + sightSwingVariation - view.angle) * M_PI));
    sf::Vector2f B(radius * std::cos((-orientation + sightSwingVariation + view.angle) * M_PI), radius * std::sin((-orientation + sightSwingVariation + view.angle) * M_PI));

    triangle.setPoint(1, A);
    triangle.setPoint(2, B);

    triangle.setPosition(sf::Vector2f(position));

    return triangle;
}


