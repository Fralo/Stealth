//
// Created by mattia on 01/09/20.
//

#include "KilledEnemyObserver.hpp"

void KilledEnemyObserver::update() {
    enemyKilled++;
    std::cout<<"KilledEnemyObserver::update() say : new enemy killed"<<std::endl;
}
