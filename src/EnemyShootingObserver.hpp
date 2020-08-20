//
// Created by mattia on 20/08/20.
//

#ifndef STEALTH_ENEMYSHOOTINGOBSERVER_HPP
#define STEALTH_ENEMYSHOOTINGOBSERVER_HPP


#include "Enemy.hpp"

class Enemy;

class EnemyShootingObserver {

public :
    virtual void enemyShoots(Enemy * enemy) = 0;

};


#endif //STEALTH_ENEMYSHOOTINGOBSERVER_HPP
