//
// Created by mattia on 30/08/20.
//

#ifndef STEALTH_PLAYERLIFEOBSERVABLE_HPP
#define STEALTH_PLAYERLIFEOBSERVABLE_HPP


class PlayerLifeObservable {

public :
    virtual ~PlayerLifeObservable() {
        std::cout << "Goodbye, I was the EnemyShootingObserver"<<std::endl;
    }
    virtual void changePlayerLife(int damage) = 0;

};


#endif //STEALTH_PLAYERLIFEOBSERVABLE_HPP
