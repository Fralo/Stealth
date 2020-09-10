//
// Created by mattia on 10/08/20.
//

#include "MathHelper.hpp"

float MathHelper::distanceBetweenTwoPoints(sf::Vector2f p1, sf::Vector2f p2) {
    return sqrtf((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool MathHelper::hasLineOfSight(sf::Vector2f point1, sf::Vector2f point2, sf::Rect<float> rect) {
    bool top = checkLineIntersection(point1.x, point1.y, point2.x, point2.y,
                                     rect.left,
                                     rect.top,
                                     rect.left + rect.width,
                                     rect.top);
    bool left = checkLineIntersection(point1.x, point1.y, point2.x, point2.y,
                                      rect.left,
                                      rect.top,
                                      rect.left,
                                      rect.top - rect.height);
    bool bottom = checkLineIntersection(point1.x, point1.y, point2.x, point2.y,
                                        rect.top,
                                        rect.top - rect.height,
                                        rect.left + rect.width,
                                        rect.top - rect.height);
    bool right = checkLineIntersection(point1.x, point1.y, point2.x, point2.y,
                                       rect.left + rect.width,
                                       rect.top - rect.height,
                                       rect.left + rect.width,
                                       rect.top);

    return (top || left || bottom || right);
}

bool MathHelper::checkLineIntersection(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
    float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
    float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

    return uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1;
}

/**
   Return the angle between two vectors on a plane
   The angle is from vector 1 to vector 2, positive anticlockwise
   The result is between -pi -> pi
*/
double MathHelper::Angle2D(double x1, double y1, double x2, double y2) {
    double dtheta = atan2(y2, x2) - atan2(y1, x1);
    while (dtheta > M_PI)
        dtheta -= 2 * M_PI;
    while (dtheta < -M_PI)
        dtheta += 2 * M_PI;

    return (dtheta);
}

bool MathHelper::isTargetInside(std::vector<sf::Vector2f> coordinates, sf::Vector2f target) {
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
 * Compute the sum of the angles made between the test point and each pair of points making up the polygon.
 * If it is 2*pi, then it is an interior point. If it is 0, then it is an exterior point.
*/

std::vector<sf::Vector2f>
MathHelper::getVertices(unsigned int distance, float angle, double orientation, double sightSwingVariation) {
    std::vector<sf::Vector2f> vertices;
    double radius = distance / std::cos(M_PI * angle / 2);

    sf::Vector2f A(radius * std::cos((-orientation + sightSwingVariation - angle / 2) * M_PI),
                   radius * std::sin((-orientation + sightSwingVariation - angle / 2) * M_PI));
    sf::Vector2f B(radius * std::cos((-orientation + sightSwingVariation + angle / 2) * M_PI),
                   radius * std::sin((-orientation + sightSwingVariation + angle / 2) * M_PI));

    vertices.push_back(A);
    vertices.push_back(B);

    return vertices;
}

sf::Vector2f MathHelper::getAbsoluteCoordinates(sf::Vector2f relatives, sf::Vector2f pos) {
    sf::Vector2f absolute;
    absolute.x = relatives.x + pos.x;
    absolute.y = relatives.y + pos.y;

    return absolute;
}
