//
// Created by vivedo on 09/05/20.
//

#ifndef STEALTH_LOADSCREEN_HPP
#define STEALTH_LOADSCREEN_HPP

#include <cmath>
#include "GameState.hpp"
#include "Stealth.hpp"
#include "MainMenu.hpp"

class LoadScreen : public GameState {
public:
    void init(Stealth &stealth) override;

    void update(Stealth &stealth) override;

protected:
    void handleEvent(Stealth &stealth, sf::Event &event) override;

private:
    sf::Clock clock;
    sf::Texture splashTexture;
    sf::Sprite splashSprite;
    sf::Font splashFont;
    sf::Text splashTxt;
    sf::Texture unifiTexture;
    sf::Sprite unifiSprite;
    sf::Font creditsFont;
    sf::Text creditsTxt;
};


#endif //STEALTH_LOADSCREEN_HPP
