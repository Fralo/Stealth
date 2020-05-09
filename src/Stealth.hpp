//
// Created by vivedo on 09/05/20.
//

#ifndef STEALTH_STEALTH_HPP
#define STEALTH_STEALTH_HPP

#include <SFML/Graphics.hpp>
#include <forward_list>
#include "GameObject.hpp"


class Stealth {
public:
    Stealth();


private:
    sf::RenderWindow window;
    std::forward_list<GameObject*> gameObjects;



    void pollEvents();

    void loadGame();



};


#endif //STEALTH_STEALTH_HPP
