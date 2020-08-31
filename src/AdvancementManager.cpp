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

void AdvancementManager::update() {

    /*
     * TODO: Objectives:
     *
     * if objective == kill 10 enemyes
     *      if advancements.enemyKilled >= 10
     *          stealth.changeState(new WonScreen())
     *
     *  else if objective == another objective
     *      if objective.isComplete()
     *          stealth.changeState(new WonScreen())
     *
     *   WonScreen : GameState
     */

}
