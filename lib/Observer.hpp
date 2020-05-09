//
// Created by vivedo on 13/04/20.
//

#ifndef OBSERVER_HPP
#define OBSERVER_HPP

template <class T>
class Observer {
private:
    virtual void handle(T next) = 0;

    template <class F>
    friend class Subject;
};


#endif //OBSERVER_HPP
