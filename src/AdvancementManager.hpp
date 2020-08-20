//
// Created by vivedo on 10/08/20.
//

#ifndef STEALTH_ADVANCEMENTMANAGER_HPP
#define STEALTH_ADVANCEMENTMANAGER_HPP


#include "EnemyShootingObserver.hpp"

class AdvancementManager : public EnemyShootingObserver{
public:
    void enemyShoots() override;

private:

    struct Advancements{
        int enemyKilled = 0;
        int walked = 0;
        bool isStealth = true;
    };

    Advancements advancements;


};


#endif //STEALTH_ADVANCEMENTMANAGER_HPP
