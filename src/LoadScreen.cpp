//
// Created by vivedo on 09/05/20.
//

#include "LoadScreen.hpp"

void LoadScreen::init(Stealth &stealth) {
    stealth.window.setMouseCursorVisible(false);

    splashTexture.loadFromFile("../res/splashscreen.png");
    splashSprite.setTexture(splashTexture);

    sf::FloatRect splashSpriteRect = splashSprite.getLocalBounds();
    splashSprite.setOrigin(splashSpriteRect.left + splashSpriteRect.width / 2.0f,
                           splashSpriteRect.top + splashSpriteRect.height / 2.0f);

    splashFont.loadFromFile("../res/fonts/CaptureIt-Regular.ttf");
    splashTxt.setFont(splashFont);
    splashTxt.setCharacterSize(150);
    splashTxt.setString("STEALTH");

    sf::FloatRect splashTxtRect = splashTxt.getLocalBounds();
    splashTxt.setOrigin(splashTxtRect.left + splashTxtRect.width / 2.0f,
                        splashTxtRect.top + splashTxtRect.height / 2.0f);

    unifiTexture.loadFromFile("../res/unifi.png");
    unifiSprite.setTexture(unifiTexture);

    creditsFont.loadFromFile("../res/fonts/SpecialElite-Regular.ttf");
    creditsTxt.setFont(creditsFont);
    creditsTxt.setCharacterSize(24);
    creditsTxt.setLineSpacing(1.5);
    creditsTxt.setString("Leonardo Fralini\nMattia Marilli\nEdoardo Viviani");

    clock.restart();
}

void LoadScreen::update(Stealth &stealth) {
    pollEvents(stealth);

    int millis = clock.getElapsedTime().asMilliseconds();
    sf::Vector2u windowSize = stealth.window.getSize();

    // splash bg
    splashSprite.setPosition(sf::Vector2f(windowSize) / 2.0f);
    // game title
    splashTxt.setPosition(sf::Vector2f(windowSize) / 2.0f);
    // unifi logo
    sf::Vector2u unifiTextureSize = unifiTexture.getSize();
    unifiSprite.setPosition(20, windowSize.y - unifiTextureSize.y - 20);
    // credits
    sf::FloatRect creditsTxtRect = creditsTxt.getLocalBounds();
    creditsTxt.setPosition(40 + unifiTextureSize.x,
                           windowSize.y - unifiTextureSize.y - 20 + (unifiTextureSize.y - creditsTxtRect.height) / 2);

    // draw
    stealth.window.clear();

    stealth.window.draw(splashSprite);
    stealth.window.draw(splashTxt);
    stealth.window.draw(unifiSprite);
    stealth.window.draw(creditsTxt);

    if (millis < 1000) {
        sf::RectangleShape rect(sf::Vector2f(800, 600));
        rect.setFillColor(sf::Color(0, 0, 0, 255 - millis / 1000.0f * 255));
        stealth.window.draw(rect);
    }

    stealth.window.display();

    // change state after 5s
    if (millis > 5000)
        stealth.changeState(new MainMenu());
}

void LoadScreen::handleEvent(Stealth &stealth, sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed) {
        stealth.changeState(new MainMenu());
    }
}
