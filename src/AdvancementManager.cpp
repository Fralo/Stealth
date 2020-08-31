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

void AdvancementManager::changePlayerLife(std::shared_ptr<Player> player, int damage) {
    player->getHealth();
    advancements.playerLife -= damage;
    if(advancements.playerLife == 0)
    {
        stealth.popStack();
        std::cout<<"PlayerLifeObserver -> Player Ucciso : Missione Fallita"<<std::endl;
    }
}

void AdvancementManager::isTargetDestroyed(int damage) {
    advancements.towerHealth -= damage;
    if(advancements.towerHealth == 0)
    {
        stealth.popStack();
        std::cout<<"MissionOneObserver -> Missione 1 Completata : Hai vinto!"<<std::endl;
    }

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
