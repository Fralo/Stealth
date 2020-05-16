//
// Created by vivedo on 09/05/20.
//

#ifndef STEALTH_SEEKSTRATEGY_HPP
#define STEALTH_SEEKSTRATEGY_HPP

#define GRID_SCALE_FACTOR 16

#include <list>
#include <vector>
#include <cfloat>
#include <vector>
#include <iostream>
#include "Strategy.hpp"
#include "Astar.hpp"
#include "Object.hpp"
#include "Game.hpp"

class SeekStrategy : public Strategy {
public:
    sf::Vector2f getNextMove(GameObject &gameObject, Game &game) override;
    void addLocation(sf::Vector2i location);
    
private:
    std::vector<Vector2u8> locations;
    int currentTarget = 0;

    sf::Clock cacheTime;
    Path *path = nullptr;
};


#endif //STEALTH_SEEKSTRATEGY_HPP
