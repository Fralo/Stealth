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
#include "Strategy.hpp"
#include "AStar2.hpp"
#include "Object.hpp"
#include "Game.hpp"

class SeekStrategy : public Strategy {
public:
    sf::Vector2f getNextMove(GameObject &gameObject, Game &game) override;
    void addLocation(sf::Vector2i location);
    
private:
    std::vector<sf::Vector2<uint8>> locations;
    int currentTarget = 0;

    sf::Clock cacheTime;
    Path *path = nullptr;

    int cache = 0;
};


#endif //STEALTH_SEEKSTRATEGY_HPP
