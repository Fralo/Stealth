//
// Created by vivedo on 09/05/20.
//

#include "MainMenu.hpp"

MainMenu::~MainMenu() {
    this->unload();
}

void MainMenu::init(Stealth &stealth) {
    stealth.window.setMouseCursorVisible(true);

    bgTexture.loadFromFile("../res/map.png");
    bgSprite.setTexture(bgTexture);
    bgSprite.setScale(1.2f, 1.2f);
    sf::FloatRect bgSpriteRect = bgSprite.getLocalBounds();
    bgSprite.setOrigin(bgSpriteRect.left + bgSpriteRect.width / 2.0f, bgSpriteRect.top + bgSpriteRect.height / 2.0f);

    titleFont.loadFromFile("../res/fonts/CaptureIt-Regular.ttf");
    mainMenuTxt.setFont(titleFont);
    mainMenuTxt.setCharacterSize(100);
    mainMenuTxt.setString("MAIN MENU");
    mainMenuTxt.setFillColor(sf::Color(0xbb, 0xa1, 0x60));
    sf::FloatRect mainMenuRect = mainMenuTxt.getLocalBounds();
    mainMenuTxt.setOrigin(mainMenuRect.left + mainMenuRect.width / 2.0f, mainMenuRect.top + mainMenuRect.height / 2.0f);

    selectionFont.loadFromFile("../res/fonts/SpecialElite-Regular.ttf");
    newGameTxt.setFont(selectionFont);
    newGameTxt.setCharacterSize(42);
    newGameTxt.setString("New Game");
    newGameTxt.setFillColor(sf::Color(0xdd, 0xce, 0xa9));
    sf::FloatRect newGameRect = newGameTxt.getLocalBounds();
    newGameTxt.setOrigin(newGameRect.left + newGameRect.width / 2.0f, newGameRect.top + newGameRect.height / 2.0f);

    quitTxt.setFont(selectionFont);
    quitTxt.setCharacterSize(42);
    quitTxt.setString("Quit");
    sf::FloatRect quitRect = quitTxt.getLocalBounds();
    quitTxt.setOrigin(quitRect.left + quitRect.width / 2.0f, quitRect.top + quitRect.height / 2.0f);

    selectionSfxBuffer.loadFromFile("../res/music/selection_sfx.ogg");
    selectionSfx.setBuffer(selectionSfxBuffer);
    selectionSfx.setVolume(25);
    unselectionSfxBuffer.loadFromFile("../res/music/selection_sfx2.ogg");
    unselectionSfx.setBuffer(unselectionSfxBuffer);
    unselectionSfx.setVolume(25);

    selectCursor.loadFromSystem(sf::Cursor::Hand);
    defaultCursor.loadFromSystem(sf::Cursor::Arrow);

    music = new sf::Music();
    music->openFromFile("../res/music/Stealth_menu.ogg");
    music->setLoop(true);
    music->setVolume(50);
    music->play();
}

void MainMenu::unload() {
    // Unload heavy assets
    delete music;

    // TODO: unload more heavy things
}

void MainMenu::update(Stealth &stealth) {
    pollEvents(stealth);

    int millis = clock.getElapsedTime().asMilliseconds();
    sf::Vector2u windowSize = stealth.window.getSize();

    // background
    bgSprite.setPosition(sf::Vector2f(windowSize) / 2.0f
                        + sf::Vector2f(50 * std::cos(3 * millis / 4000.0f), 50 * std::sin(2 * millis / 4000.0f))); // lissajous a = 3, b = 2
    // menu title
    mainMenuTxt.setPosition(windowSize.x / 2.0f, 100);

    // select options
    if(stealth.window.hasFocus()){
        if(newGameTxt.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(stealth.window)))) {
            if(selectedOption != NEW_GAME) {
                selectionSfx.play();
                selectedOption = NEW_GAME;
                stealth.window.setMouseCursor(selectCursor);
            }
        } else if (quitTxt.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(stealth.window)))) {
            if(selectedOption != QUIT) {
                selectionSfx.play();
                selectedOption = QUIT;
                stealth.window.setMouseCursor(selectCursor);
            }
        } else {
            if(selectedOption != NONE) {
                unselectionSfx.play();
                selectedOption = NONE;
                stealth.window.setMouseCursor(defaultCursor);
            }
        }
    }

    newGameTxt.setPosition(windowSize.x / 2.0f, 250);
    newGameTxt.setFillColor(selectedOption == NEW_GAME ? selectedColor : defaultColor);

    quitTxt.setPosition(windowSize.x / 2.0f, 320);
    quitTxt.setFillColor(selectedOption == QUIT ? selectedColor : defaultColor);


    // draw
    stealth.window.clear();

    stealth.window.draw(bgSprite);
    stealth.window.draw(mainMenuTxt);
    stealth.window.draw(newGameTxt);
    stealth.window.draw(quitTxt);

    stealth.window.display();
}

void MainMenu::handleEvent(Stealth &stealth, sf::Event &event) {
    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        switch(selectedOption) {
            case QUIT:
                stealth.window.close();
                break;
            case NEW_GAME:
                stealth.changeState(new Game());
                break;
            default:
                break;
        }
    }
}