//
// Created by vivedo on 11/05/20.
//

#ifndef STEALTH_OBSTACLE_HPP
#define STEALTH_OBSTACLE_HPP

#include <SFML/Graphics.hpp>

class Obstacle : public sf::IntRect {
public:
    bool destroyable = false;

};


#endif //STEALTH_OBSTACLE_HPP
