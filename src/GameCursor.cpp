//
// Created by vivedo on 13/05/20.
//

#include "GameCursor.hpp"

GameCursor::GameCursor() {
    cursorTexture.loadFromFile(resource("cursors.png"));
}

void GameCursor::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Sprite cursor;
    cursor.setTexture(cursorTexture);
    cursor.setTextureRect(sf::IntRect(0, 96, 96, 96));
    cursor.setPosition(position);
    cursor.setScale(sf::Vector2f(1, 1));
    target.draw(cursor);
}

void GameCursor::update(Game &game, sf::RenderWindow &window) {
    position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}
