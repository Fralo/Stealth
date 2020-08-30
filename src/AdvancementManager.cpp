//
// Created by vivedo on 10/08/20.
//

#include "AdvancementManager.hpp"

void AdvancementManager::enemyShoots() {
    advancements.enemyKilled ++;
}

void AdvancementManager::changeStealthStatus() {
    advancements.isStealth = false;
}

void AdvancementManager::updateWalked() {

}

void AdvancementManager::changePlayerLife(int damage) {
    advancements.playerLife -= damage;
}
