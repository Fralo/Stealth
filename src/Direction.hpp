//
// Created by vivedo on 23/07/20.
//

#ifndef STEALTH_DIRECTION_HPP
#define STEALTH_DIRECTION_HPP


#include <SFML/Graphics.hpp>

class Direction {
public:
    enum Directions {
        NORTH,
        NORTH_EAST,
        EAST,
        SUD_EAST,
        SUD,
        SUD_OVEST,
        OVEST,
        NORTH_OVEST
    };

    Direction() = default;
    constexpr Direction(Directions dir) : dir(dir) {}
    explicit Direction(sf::Vector2f &vect) {
        if(vect.x > 0 && vect.y == 0) dir = Directions::EAST;
        else if(vect.x > 0 && vect.y > 0) dir = Directions::SUD_EAST;
        else if(vect.x == 0 && vect.y > 0) dir = Directions::SUD;
        else if(vect.x < 0 && vect.y > 0) dir = Directions::SUD_OVEST;
        else if(vect.x < 0 && vect.y == 0) dir = Directions::OVEST;
        else if(vect.x < 0 && vect.y < 0) dir = Directions::NORTH_OVEST;
        else if(vect.x == 0 && vect.y < 0) dir = Directions::NORTH;
        else if(vect.x > 0 && vect.y < 0) dir = Directions::NORTH_EAST;
    }
    operator Directions() const { return dir; }
    explicit operator bool() = delete;

private:
    Directions dir;
};


#endif //STEALTH_DIRECTION_HPP
