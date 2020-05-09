//
// Created by vivedo on 09/05/20.
//

#ifndef STEALTH_SEEKSTRATEGY_HPP
#define STEALTH_SEEKSTRATEGY_HPP

#include <forward_list>
#include "Strategy.hpp"

class SeekStrategy : Strategy {
public:
    SeekStrategy(int x, int y, int o, std::forward_list<sf::Vector2i> &l);

    sf::Vector2f getNextMove(GameObject &gameObject) override;
    
private:
    const std::forward_list<sf::Vector2i> *locations;
    int x;
    int y;
};


#endif //STEALTH_SEEKSTRATEGY_HPP
