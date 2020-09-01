//
// Created by mattia on 01/09/20.
//

#ifndef STEALTH_ADVANCEMENTMANAGEROBSERVER_HPP
#define STEALTH_ADVANCEMENTMANAGEROBSERVER_HPP

#include <iostream>

class AdvancementManagerObserver {
public:
    virtual ~AdvancementManagerObserver() {
        std::cout << "Goodbye, I was the AdvancementManagerObserver"<<std::endl;
    }
    virtual void update() = 0;
};


#endif //STEALTH_ADVANCEMENTMANAGEROBSERVER_HPP
