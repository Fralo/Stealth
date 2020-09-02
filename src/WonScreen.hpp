//
// Created by mattia on 02/09/20.
//

#ifndef STEALTH_WONSCREEN_HPP
#define STEALTH_WONSCREEN_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameState.hpp"
#include "Stealth.hpp"
#include "Game.hpp"


class WonScreen : public GameState{

public:
    ~WonScreen();
    WonScreen(int enemyKilled, bool isStealth);
    void init(Stealth &stealth) override;
    void update(Stealth &stealth) override;
    void unload();

protected:
    void handleEvent(Stealth &stealth, sf::Event &event) override;

private:
    sf::Clock clock;
    sf::Music *music;
    sf::SoundBuffer selectionSfxBuffer;
    sf::SoundBuffer unselectionSfxBuffer;
    sf::Sound selectionSfx;
    sf::Sound unselectionSfx;
    sf::Font titleFont;
    sf::Texture bgTexture;
    sf::Sprite bgSprite;
    sf::Text mainMenuTxt;
    sf::Font selectionFont;
    sf::Text newGameTxt;
    sf::Text quitTxt;
    sf::Font achievementFont;
    sf::Text enemyKilledTxt;
    sf::Text isStealthTxt;

    sf::Cursor selectCursor;
    sf::Cursor defaultCursor;

    MenuOption selectedOption = NONE;

    int enemyKilled;
    bool isStealth;

    const sf::Color selectedColor = sf::Color(152, 251, 152);
    const sf::Color defaultColor = sf::Color(50,205,50);
};


#endif //STEALTH_WONSCREEN_HPP
