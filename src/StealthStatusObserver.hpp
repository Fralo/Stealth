//
// Created by mattia on 01/09/20.
//

#ifndef STEALTH_STEALTHSTATUSOBSERVER_HPP
#define STEALTH_STEALTHSTATUSOBSERVER_HPP


#include "AdvancementManagerObserver.hpp"

class StealthStatusObserver : public AdvancementManagerObserver{
public:
    void update() override;
    bool isStealth = true;
};


#endif //STEALTH_STEALTHSTATUSOBSERVER_HPP
