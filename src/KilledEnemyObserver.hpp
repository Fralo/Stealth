//
// Created by mattia on 01/09/20.
//

#ifndef STEALTH_KILLEDENEMYOBSERVER_HPP
#define STEALTH_KILLEDENEMYOBSERVER_HPP


#include "AdvancementManagerObserver.hpp"

class KilledEnemyObserver : public AdvancementManagerObserver{
public:
    void update() override;
    int enemyKilled = 0;
};


#endif //STEALTH_KILLEDENEMYOBSERVER_HPP
