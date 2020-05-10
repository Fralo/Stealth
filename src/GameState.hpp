//
// Created by vivedo on 09/05/20.
//

#ifndef STEALTH_GAMESTATE_HPP
#define STEALTH_GAMESTATE_HPP

#include <SFML/Graphics.hpp>

class Stealth;

class GameState {
public:
    virtual ~GameState() = default;
    virtual void init(Stealth &stealth) = 0;
    virtual void update(Stealth &stealth) = 0;

protected:
    /*
     * Util methods used to handle basic events as Event::Close
     * and slim event polling code in GameStates
     */
    virtual void handleEvent(Stealth &stealth, sf::Event &event) {};
    void pollEvents(Stealth &stealth);
};


#endif //STEALTH_GAMESTATE_HPP