//
// Created by mattia on 10/08/20.
//

#include "MathHelper.hpp"

float MathHelper::distanceBetweenTwoPoints(sf::Vector2f p1, sf::Vector2f p2) {
    return sqrtf((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool MathHelper::hasLineOfSight(sf::Vector2f point1,sf::Vector2f point2,sf::Rect<float> rect) {
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

    return !(top || left || bottom || right);
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
