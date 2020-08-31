//
// Created by vivedo on 10/08/20.
//

#include "AdvancementManager.hpp"

void AdvancementManager::enemyShoots() {
    advancements.enemyKilled ++;
    std::cout<<"EnemyShootingObserver -> Totale Nemici Uccisi : "<<advancements.enemyKilled<<std::endl;
}

void AdvancementManager::changeStealthStatus() {
    if(advancements.isStealth == true)
    {
        advancements.isStealth = false;
        std::cout<<"StealthStatusObserver -> Player Visto"<<std::endl;
    }

}

void AdvancementManager::updateWalked() {

}

void AdvancementManager::changePlayerLife(int damage) {
    advancements.playerLife -= damage;
    if(advancements.playerLife == 0)
    {
        stealth.popStack();
        std::cout<<"PlayerLifeObserver -> Player Ucciso : Missione Fallita"<<std::endl;
    }
}

void AdvancementManager::isTargetDestroyed() {
    advancements.missionOne = true;
    std::cout<<"MissionOneObserver -> Missione 1 Completata : Hai vinto!"<<std::endl;
    stealth.popStack();
}
