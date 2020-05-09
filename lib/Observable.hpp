//
// Created by vivedo on 13/04/20.
//

#ifndef OBSERVABLE_HPP
#define OBSERVABLE_HPP

#include <forward_list>
#include "Observer.hpp"

template <class T>
class Observable {
public:
    void subscribe(Observer<T> &observer) {
        for(Observer<T> *listObserver : observers)
            if(listObserver == &observer)
                return;

        observers.push_front(&observer);
    }

    void unsubscribe(Observer<T> &observer) {
        observers.remove(&observer);
    }

    void clear() {
        observers.clear();
    }

    void next(T next) {
        for(Observer<T> *listObserver : observers)
            listObserver->handle(next);
    }

private:
    std::forward_list<Observer<T>*> observers;
};

#endif //OBSERVABLE_HPP
