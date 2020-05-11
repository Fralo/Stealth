//
// Created by vivedo on 09/05/20.
//

#ifndef STEALTH_SEEKSTRATEGY_HPP
#define STEALTH_SEEKSTRATEGY_HPP

#include <forward_list>
#include <vector>
#include <float.h>
#include <vector>
#include "Strategy.hpp"
#include "AStar.hpp"
#include "Obstacle.hpp"

class SeekStrategy : Strategy {
public:
    SeekStrategy(int x, int y, int o, std::forward_list<sf::Vector2i> &l, std::forward_list<Obstacle*> &obs);

    sf::Vector2f getNextMove(GameObject &gameObject) override;
    
private:
    const std::forward_list<sf::Vector2i> *locations;
    int x;
    int y;
    int nLocation;
    int currentTarget = 0;
    AStar *aStar = new AStar;
    bool isArrivedToTarget(Node check,Node Target);

};


#endif //STEALTH_SEEKSTRATEGY_HPP
