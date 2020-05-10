//
// Created by vivedo on 09/05/20.
//

#ifndef STEALTH_GAME_HPP
#define STEALTH_GAME_HPP


#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "Stealth.hpp"

class Game : public GameState {
public:
    void init(Stealth &stealth) override;

    void update(Stealth &stealth) override;

protected:
    void handleEvent(Stealth &stealth, sf::Event &event) override;
};


#endif //STEALTH_GAME_HPP
