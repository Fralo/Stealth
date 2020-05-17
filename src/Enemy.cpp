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

    //generate the vector of vertices to find the player
    std::vector<sf::Vector2f> coordinates;
    coordinates.push_back(this->position);
    coordinates.push_back(getAbsoluteCoordinates(getVertices().at(0)));
    coordinates.push_back(getAbsoluteCoordinates(getVertices().at(1)));

    if(distanceBetweenTwoPoints(game.player->position,this->position) < distanceBetweenTwoPoints(coordinates.at(1),this->position))
        if(isTargetInside(coordinates, game.player->position))
            strategy = new HunterStrategy();

    sf::Vector2f next = strategy->getNextMove(*this, game);

    if(distanceBetweenTwoPoints(this->position,game.player->position) > weapon.distanceOfUse)
    {

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
    else {
       // std::cout << "In Linea di tiro"<<std::endl;
    }

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

/*
 * Compute the sum of the angles made between the test point and each pair of points making up the polygon.
 * If it is 2*pi, then it is an interior point. If it is 0, then it is an exterior point.
*/

bool Enemy::isTargetInside(std::vector<sf::Vector2f> coordinates, sf::Vector2f target) {


    float x1,y1,x2,y2;
    double angle = 0;

    for(int i = 0; i<coordinates.size(); i++)
    {
        x1 = coordinates.at(i).x - target.x;
        y1 = coordinates.at(i).y - target.y;
        x2 = coordinates.at((i+1) % 3).x - target.x;
        y2 = coordinates.at((i+1) %3 ).y - target.y;
        angle += Angle2D(x1,y1,x2,y2);
    }

    if (abs(angle) < M_PI)
        return false;
    else
        return true;
}

/*
   Return the angle between two vectors on a plane
   The angle is from vector 1 to vector 2, positive anticlockwise
   The result is between -pi -> pi
*/

double Enemy::Angle2D(float x1, float y1, float x2, float y2) {
    double dtheta,theta1,theta2;

    theta1 = atan2(y1,x1);
    theta2 = atan2(y2,x2);
    dtheta = theta2 - theta1;
    while (dtheta > M_PI)
        dtheta -= 2*M_PI;
    while (dtheta < -M_PI)
        dtheta += 2*M_PI;

    return(dtheta);
}

sf::Vector2f Enemy::getAbsoluteCoordinates(sf::Vector2f relatives) const {
    sf::Vector2f absolute;
    absolute.x = relatives.x + this->position.x;
    absolute.y = relatives.y + this->position.y;

    return absolute;
}

float Enemy::distanceBetweenTwoPoints(sf::Vector2f p1,sf::Vector2f p2) {

    return sqrtf((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}










