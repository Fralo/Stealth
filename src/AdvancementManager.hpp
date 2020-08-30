//
// Created by vivedo on 10/08/20.
//

#ifndef STEALTH_ADVANCEMENTMANAGER_HPP
#define STEALTH_ADVANCEMENTMANAGER_HPP


#include "EnemyShootingObserver.hpp"
#include "IsStealthObserver.hpp"
#include "WalkObserver.hpp"
#include "PlayerLifeObservable.hpp"

class AdvancementManager : public EnemyShootingObserver, public IsStealthObserver, public WalkObserver, public PlayerLifeObservable{
public:
    void enemyShoots() override;
    void changeStealthStatus() override;
    void updateWalked() override;
    void changePlayerLife(int damage) override;

private:

    struct Advancements{
        int enemyKilled = 0;
        int walked = 0;
        bool isStealth = true;
        int playerLife = 100;
    };
    Advancements advancements;

};


#endif //STEALTH_ADVANCEMENTMANAGER_HPP
