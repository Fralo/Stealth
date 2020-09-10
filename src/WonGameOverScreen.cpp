//
// Created by mattia on 02/09/20.
//

#include "WonGameOverScreen.hpp"

WonGameOverScreen::~WonGameOverScreen() {
    this->unload();
}

void WonGameOverScreen::init(Stealth &stealth) {
    stealth.window.setMouseCursorVisible(true);

    bgTexture.loadFromFile("../res/map_ascii.png");
    bgSprite.setTexture(bgTexture);
    bgSprite.setScale(1.0f, 1.0f);
    sf::FloatRect bgSpriteRect = bgSprite.getLocalBounds();
    bgSprite.setOrigin(bgSpriteRect.left + bgSpriteRect.width / 2.0f, bgSpriteRect.top + bgSpriteRect.height / 2.0f);

    titleFont.loadFromFile("../res/fonts/CaptureIt-Regular.ttf");
    mainMenuTxt.setFont(titleFont);
    mainMenuTxt.setCharacterSize(100);
    if (won)
        mainMenuTxt.setString("WIN");
    else
        mainMenuTxt.setString("Game Over");
    mainMenuTxt.setFillColor(sf::Color(124, 252, 0));
    sf::FloatRect mainMenuRect = mainMenuTxt.getLocalBounds();
    mainMenuTxt.setOrigin(mainMenuRect.left + mainMenuRect.width / 2.0f, mainMenuRect.top + mainMenuRect.height / 2.0f);

    selectionFont.loadFromFile("../res/fonts/SpecialElite-Regular.ttf");
    newGameTxt.setFont(selectionFont);
    newGameTxt.setCharacterSize(42);
    newGameTxt.setString("New Game");
    sf::FloatRect newGameRect = newGameTxt.getLocalBounds();
    newGameTxt.setOrigin(newGameRect.left + newGameRect.width / 2.0f, newGameRect.top + newGameRect.height / 2.0f);

    quitTxt.setFont(selectionFont);
    quitTxt.setCharacterSize(42);
    quitTxt.setString("Quit");
    sf::FloatRect quitRect = quitTxt.getLocalBounds();
    quitTxt.setOrigin(quitRect.left + quitRect.width / 2.0f, quitRect.top + quitRect.height / 2.0f);

    //achievement
    achievementFont.loadFromFile("../res/fonts/OpenSans-Regular.ttf");
    enemyKilledTxt.setFont(achievementFont);
    enemyKilledTxt.setCharacterSize(30);
    enemyKilledTxt.setString("Enemy Killed : " + std::to_string(enemyKilled));
    sf::FloatRect enemyKilledRect = enemyKilledTxt.getLocalBounds();
    enemyKilledTxt.setOrigin(enemyKilledRect.left + enemyKilledRect.width / 2.0f,
                             enemyKilledRect.top + enemyKilledRect.height / 2.0f);

    isStealthTxt.setFont(achievementFont);
    isStealthTxt.setCharacterSize(30);
    if (isStealth)
        isStealthTxt.setString("The player was never seen by an enemy");
    else
        isStealthTxt.setString("The player was seen by an enemy");
    sf::FloatRect isStealthRect = isStealthTxt.getGlobalBounds();
    isStealthTxt.setOrigin(isStealthRect.left + isStealthRect.width / 2.0f,
                           isStealthRect.top + isStealthRect.height / 2.0f);

    selectionSfxBuffer.loadFromFile("../res/music/selection_sfx.ogg");
    selectionSfx.setBuffer(selectionSfxBuffer);
    selectionSfx.setVolume(25);
    unselectionSfxBuffer.loadFromFile("../res/music/selection_sfx2.ogg");
    unselectionSfx.setBuffer(unselectionSfxBuffer);
    unselectionSfx.setVolume(25);

    selectCursor.loadFromSystem(sf::Cursor::Hand);
    defaultCursor.loadFromSystem(sf::Cursor::Arrow);

    music = new sf::Music();
    if (won)
        music->openFromFile("../res/music/rocky.ogg");
    else
        music->openFromFile("../res/music/gameover.ogg");
    music->setLoop(true);
    music->setVolume(100);
    music->play();
}

void WonGameOverScreen::update(Stealth &stealth) {
    pollEvents(stealth);

    int millis = clock.getElapsedTime().asMilliseconds();
    sf::Vector2u windowSize = stealth.window.getSize();

    // background
    bgSprite.setPosition(sf::Vector2f(windowSize) / 2.0f
                         + sf::Vector2f(50 * std::cos(3 * millis / 4000.0f),
                                        50 * std::sin(2 * millis / 4000.0f))); // lissajous a = 3, b = 2
    // menu title
    mainMenuTxt.setPosition(windowSize.x / 2.0f, 100);

    // select options
    if (stealth.window.hasFocus()) {
        if (newGameTxt.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(stealth.window)))) {
            if (selectedOption != NEW_GAME) {
                selectionSfx.play();
                selectedOption = NEW_GAME;
                stealth.window.setMouseCursor(selectCursor);
            }
        } else if (quitTxt.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(stealth.window)))) {
            if (selectedOption != QUIT) {
                selectionSfx.play();
                selectedOption = QUIT;
                stealth.window.setMouseCursor(selectCursor);
            }
        } else {
            if (selectedOption != NONE) {
                unselectionSfx.play();
                selectedOption = NONE;
                stealth.window.setMouseCursor(defaultCursor);
            }
        }
    }


    enemyKilledTxt.setPosition(windowSize.x / 2.0f, 220);
    isStealthTxt.setPosition(windowSize.x / 2.0f, 280);

    newGameTxt.setPosition(windowSize.x / 2.0f, 370);
    newGameTxt.setFillColor(selectedOption == NEW_GAME ? selectedColor : defaultColor);

    quitTxt.setPosition(windowSize.x / 2.0f, 440);
    quitTxt.setFillColor(selectedOption == QUIT ? selectedColor : defaultColor);

    // draw
    stealth.window.clear();

    stealth.window.draw(bgSprite);
    stealth.window.draw(mainMenuTxt);
    stealth.window.draw(newGameTxt);
    stealth.window.draw(quitTxt);
    stealth.window.draw(enemyKilledTxt);
    stealth.window.draw(isStealthTxt);

    stealth.window.display();
}

void WonGameOverScreen::unload() {
    // Unload heavy assets
    delete music;

    // TODO: unload more heavy things
}

void WonGameOverScreen::handleEvent(Stealth &stealth, sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        switch (selectedOption) {
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

WonGameOverScreen::WonGameOverScreen(int enemyKilled, bool isStealth, bool won) : enemyKilled(enemyKilled),
                                                                                  isStealth(isStealth), won(won) {}


