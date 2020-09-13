//
// Created by mattia on 13/09/20.
//

#ifndef STEALTH_ADVANCEMENTMANAGERSUBJECT_HPP
#define STEALTH_ADVANCEMENTMANAGERSUBJECT_HPP

#include <iostream>
#include <memory>
#include "AdvancementManagerObserver.hpp"

class AdvancementManagerSubject {
public:
    virtual ~AdvancementManagerSubject(){};
    virtual void subscribe(std::shared_ptr<AdvancementManagerObserver> observer, const std::type_info& classInfo ) = 0;
    virtual void unsubscribe(std::shared_ptr<AdvancementManagerObserver> observer, const std::type_info &classInfo) = 0;
    virtual void notify(const std::type_info& classInfo) = 0;
};


#endif //STEALTH_ADVANCEMENTMANAGERSUBJECT_HPP
