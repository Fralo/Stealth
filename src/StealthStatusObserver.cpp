//
// Created by mattia on 01/09/20.
//

#include "StealthStatusObserver.hpp"

void StealthStatusObserver::update() {
    if (isStealth == true) {
        isStealth = false;
        std::cout << "StealthStatusObserver::update() say : an enemy saw the player" << std::endl;
    }
}
