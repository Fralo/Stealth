//
// Created by mattia on 31/08/20.
//

#ifndef STEALTH_MISSIONONEOBSERVER_HPP
#define STEALTH_MISSIONONEOBSERVER_HPP

#include <iostream>

class MissionOneObserver {
public:
    virtual ~MissionOneObserver() {
        std::cout << "Goodbye, I was the EnemyShootingObserver"<<std::endl;
    }
    virtual void isTargetDestroyed(int health) = 0;

};

#endif //STEALTH_MISSIONONEOBSERVER_HPP
