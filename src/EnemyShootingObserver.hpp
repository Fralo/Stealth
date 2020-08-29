//
// Created by mattia on 20/08/20.
//

#ifndef STEALTH_ENEMYSHOOTINGOBSERVER_HPP
#define STEALTH_ENEMYSHOOTINGOBSERVER_HPP


#include "Enemy.hpp"

class Enemy;

class EnemyShootingObserver {

public :
    virtual ~EnemyShootingObserver() {
        std::cout << "Goodbye, I was the EnemyShootingObserver"<<std::endl;
    }
    virtual void enemyShoots() = 0;

};


#endif //STEALTH_ENEMYSHOOTINGOBSERVER_HPP
