//
// Created by mattia on 10/08/20.
//

#ifndef STEALTH_MATHHELPER_HPP
#define STEALTH_MATHHELPER_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "Tile.hpp"
#include "Object.hpp"
#include <cmath>

class MathHelper {
public:
    MathHelper() = delete;
    static float distanceBetweenTwoPoints(sf::Vector2f p1,sf::Vector2f p2);
    static bool hasLineOfSight(sf::Vector2f point1,sf::Vector2f point2,sf::Rect<float> rect);
    static bool isTargetInside(std::vector<sf::Vector2f> coordinates, sf::Vector2f target);
    static bool checkLineIntersection(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
    static double Angle2D(double x1, double y1, double x2, double y2);
    static std::vector<sf::Vector2f> getVertices(unsigned  int distance,float angle, double orientation, double sightSwingVariation) ;

};

#endif //STEALTH_MATHHELPER_HPP
