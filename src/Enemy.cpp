//
//
// Created by vivedo on 09/05/20.
//

#include "Enemy.hpp"

Enemy::Enemy(sf::Vector2f position, float orientation, Weapon weapon, EnemyView view, Strategy *defaultStrategy)
        : orientation(orientation), defaultStrategy(defaultStrategy), weapon(weapon), view(view) {
    setPos(position);
    strategy = std::unique_ptr<Strategy>(defaultStrategy);
    orientationTarget = orientation;
}

void Enemy::update(const std::list<std::shared_ptr<Object>> &objects, Player &player, TiledMap &map) {
    //generate the vector of vertices to find the player
    std::vector<sf::Vector2f> coordinates;
    coordinates.push_back(getPos());
    coordinates.push_back(getAbsoluteCoordinates(getViewVertices().at(0)));
    coordinates.push_back(getAbsoluteCoordinates(getViewVertices().at(1)));


    if (MathHelper::distanceBetweenTwoPoints(player.getPos(), getPos()) <
        MathHelper::distanceBetweenTwoPoints(coordinates.at(1), getPos()))
        if (isTargetInside(coordinates, player.getPos()))
            for (const std::shared_ptr<Object>& obj : objects) {
                if (MathHelper::hasLineOfSight(obj->getPos(), player.getPos(), obj->getAbsCollisionBox()))
                    strategy = std::make_shared<HunterStrategy>();
            }

            // TODO: @fritz
            //else
            //    std::cout << "ti potrei vedere" << std::endl;

    sf::Vector2f next = strategy->getNextMove(*this, objects, player, map);

    if (MathHelper::distanceBetweenTwoPoints(getPos(), player.getPos()) > weapon.distanceOfUse - 10) {

        float movementFactor = 1;
        setPos(sf::Vector2f(getPos().x + next.x * movementFactor, getPos().y + next.y * movementFactor));

        if (next.x || next.y)
            orientationTarget = -std::atan2(next.y, next.x) / M_PI;

        if (orientation != orientationTarget) {
            double diff = orientationTarget - orientation;
            diff += (diff > 1) ? -2 : (diff < -1) ? 2 : 0;
            orientation += diff / 10;
        }
        sightSwingVariation = view.swing * std::sin(clock.getElapsedTime().asMilliseconds() / 500.0f);
    } else {
        coordinates.clear();
        coordinates.push_back(getPos());
        coordinates.push_back(getAbsoluteCoordinates(getFireVertices().at(0)));
        coordinates.push_back(getAbsoluteCoordinates(getFireVertices().at(1)));

        if (player.getHealth()>0)
            player.applyDamage(1);
    }




    const char *dir = "idle";
    switch(Direction(next)){
        case Direction::NORTH:
            dir = "walk_n";
            break;
        case Direction::NORTH_EAST:
            dir = "walk_ne";
            break;
        case Direction::EAST:
            dir = "walk_e";
            break;
        case Direction::SUD_EAST:
            dir = "walk_se";
            break;
        case Direction::SUD:
            dir = "walk_s";
            break;
        case Direction::SUD_OVEST:
            dir = "walk_so";
            break;
        case Direction::OVEST:
            dir = "walk_o";
            break;
        case Direction::NORTH_OVEST:
            dir = "walk_no";
            break;
    }

    tile = map.getAnimation("player", dir).getCurrentFrame();
}

void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    tile->setPosition(getPos().x - 30, getPos().y - 30);
    target.draw(*tile);

    sf::ConvexShape sightTriangle = getSightTraigle();
    sightTriangle.setFillColor(sf::Color(0x0, 0xd0, 0x20, 0x7f));

    target.draw(sightTriangle);

    sf::RectangleShape re({static_cast<float>(getHealth()) / 100 * 20, 2});
    re.setPosition({getPos().x - 10, getPos().y - 25});
    re.setFillColor(sf::Color::Red);

    target.draw(re);
}

/**
 * Returns an isosceles triangle shape  with a vertex on enemy position, with height parallel to enemy orientation
 * (with swing) and equal to sight.distance, angle between the two sides equal to sight.angle
 */
sf::ConvexShape Enemy::getSightTraigle() const {
    sf::ConvexShape triangle(3);
    triangle.setPoint(0, sf::Vector2f(0, 0));
    triangle.setPoint(1, getViewVertices().at(0));
    triangle.setPoint(2, getViewVertices().at(1));

    triangle.setPosition(sf::Vector2f(getPos()));
    return triangle;
}

std::vector<sf::Vector2f> Enemy::getViewVertices() const {
    std::vector<sf::Vector2f> vertices;
    double radius = view.distance / std::cos(M_PI * view.angle / 2);

    sf::Vector2f A(radius * std::cos((-orientation + sightSwingVariation - view.angle / 2) * M_PI),
                   radius * std::sin((-orientation + sightSwingVariation - view.angle / 2) * M_PI));
    sf::Vector2f B(radius * std::cos((-orientation + sightSwingVariation + view.angle / 2) * M_PI),
                   radius * std::sin((-orientation + sightSwingVariation + view.angle / 2) * M_PI));

    vertices.push_back(A);
    vertices.push_back(B);

    return vertices;

}

std::vector<sf::Vector2f> Enemy::getFireVertices() const {
    //TODO: use the angle from the weapon when it will be implemented
    std::vector<sf::Vector2f> vertices;
    double radius = weapon.distanceOfUse / std::cos(M_PI * view.angle / 2);

    sf::Vector2f A(radius * std::cos((-orientation + sightSwingVariation - view.angle / 2) * M_PI),
                   radius * std::sin((-orientation + sightSwingVariation - view.angle / 2) * M_PI));
    sf::Vector2f B(radius * std::cos((-orientation + sightSwingVariation + view.angle / 2) * M_PI),
                   radius * std::sin((-orientation + sightSwingVariation + view.angle / 2) * M_PI));

    vertices.push_back(A);
    vertices.push_back(B);

    return vertices;
}


/**
 * Compute the sum of the angles made between the test point and each pair of points making up the polygon.
 * If it is 2*pi, then it is an interior point. If it is 0, then it is an exterior point.
*/
bool Enemy::isTargetInside(std::vector<sf::Vector2f> coordinates, sf::Vector2f target) {
    float x1, y1, x2, y2;
    double angle = 0;

    for (int i = 0; i < coordinates.size(); i++) {
        x1 = coordinates.at(i).x - target.x;
        y1 = coordinates.at(i).y - target.y;
        x2 = coordinates.at((i + 1) % 3).x - target.x;
        y2 = coordinates.at((i + 1) % 3).y - target.y;
        angle += Angle2D(x1, y1, x2, y2);
    }

    return abs(angle) >= M_PI;
}

/**
   Return the angle between two vectors on a plane
   The angle is from vector 1 to vector 2, positive anticlockwise
   The result is between -pi -> pi
*/
double Enemy::Angle2D(double x1, double y1, double x2, double y2) {
    double dtheta = atan2(y2, x2) - atan2(y1, x1);
    while (dtheta > M_PI)
        dtheta -= 2 * M_PI;
    while (dtheta < -M_PI)
        dtheta += 2 * M_PI;

    return (dtheta);
}

sf::Vector2f Enemy::getAbsoluteCoordinates(sf::Vector2f relatives) const {
    sf::Vector2f absolute;
    absolute.x = relatives.x + getPos().x;
    absolute.y = relatives.y + getPos().y;

    return absolute;
}

void Enemy::applyDamage(int damage) {
    setHealth(getHealth() - damage);
}
















