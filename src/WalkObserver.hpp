//
// Created by mattia on 21/08/20.
//

#ifndef STEALTH_WALKOBSERVER_HPP
#define STEALTH_WALKOBSERVER_HPP


class WalkObserver {
public:
    virtual ~WalkObserver() {
        std::cout << "Goodbye, I was the WalkObserver"<<std::endl;
    }
    virtual void updateWalked() = 0;

};


#endif //STEALTH_WALKOBSERVER_HPP
