//
// Created by mattia on 14/05/20.
//

#ifndef STEALTH_HUNTERSTRATEGY_HPP
#define STEALTH_HUNTERSTRATEGY_HPP

#define GRID_SCALE_FACTOR 16

#include "Strategy.hpp"
#include "Astar.hpp"
#include "Game.hpp"

class HunterStrategy : public Strategy {
public:
    sf::Vector2f getNextMove(GameObject &gameObject,const std::list<std::shared_ptr<Object>> &objects,Player &player,TiledMap &map) override;

private:
    sf::Clock cacheTime;
    Path *path = nullptr;
};


#endif //STEALTH_HUNTERSTRATEGY_HPP
