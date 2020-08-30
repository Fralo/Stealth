//
// Created by vivedo on 09/05/20.
//

#ifndef STEALTH_STEALTH_HPP
#define STEALTH_STEALTH_HPP

#include <SFML/Graphics.hpp>
#include <forward_list>
#include "GameObject.hpp"
#include "LoadScreen.hpp"
#include "GameState.hpp"
class GameState;

class Stealth {
public:
    sf::RenderWindow window;

    Stealth();
    void changeState(GameState *newGameState);
    void popStack();

private:
    std::forward_list<std::unique_ptr<GameState>> stateStack;
};


#endif //STEALTH_STEALTH_HPP
