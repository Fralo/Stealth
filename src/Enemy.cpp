//
// Created by vivedo on 09/05/20.
//

#include "Enemy.hpp"
#include "HunterStrategy.hpp"

Enemy::Enemy(sf::Vector2f position, float orientation, Weapon weapon, EnemyView view, Strategy *defaultStrategy)
        : orientation(orientation), defaultStrategy(defaultStrategy), weapon(weapon), view(view) {
    this->position = position;
    strategy = defaultStrategy;
    orientationTarget = orientation;

    /*
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
            */
}

void Enemy::update(Game &game) {
    //strategy = new HunterStrategy();
    sf::Vector2f next = strategy->getNextMove(*this, game);

    float movementFactor = 1;
    position = sf::Vector2f(position.x + next.x * movementFactor, position.y + next.y * movementFactor);

    if(next.x || next.y)
        orientationTarget = -std::atan2(next.y, next.x) / M_PI;

    if(orientation != orientationTarget) {
        float diff = orientationTarget - orientation;
        diff += (diff > 1) ? -2 : (diff < -1) ? 2 : 0;
        orientation += diff / 10;
    }

    sightSwingVariation = view.swing * std::sin(clock.getElapsedTime().asMilliseconds() / 500.0f);
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

/*
 * Returns an isosceles triangle with a vertex on enemy position, with height parallel to enemy orientation (with swing)
 * and equal to sight.distance, angle between the two sides equal to sight.angle
 */
sf::ConvexShape Enemy::getSightTraigle() const {


    sf::ConvexShape triangle(3);
    triangle.setPoint(0, sf::Vector2f(0, 0));
    triangle.setPoint(1, getVertices().at(0));
    triangle.setPoint(2, getVertices().at(1));

    triangle.setPosition(sf::Vector2f(position));
    return triangle;
}

std::vector<sf::Vector2f> Enemy::getVertices() const{
    std::vector<sf::Vector2f>  vertices;
    float radius = view.distance / std::cos(M_PI * view.angle / 2);

    sf::Vector2f A(radius * std::cos((-orientation + sightSwingVariation - view.angle/2) * M_PI), radius * std::sin((-orientation + sightSwingVariation - view.angle/2) * M_PI));
    sf::Vector2f B(radius * std::cos((-orientation + sightSwingVariation + view.angle/2) * M_PI), radius * std::sin((-orientation + sightSwingVariation + view.angle/2) * M_PI));

    vertices.push_back(A);
    vertices.push_back(B);

    return vertices;

}








