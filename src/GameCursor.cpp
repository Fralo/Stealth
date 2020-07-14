//
// Created by vivedo on 13/05/20.
//

#include "GameCursor.hpp"

GameCursor::GameCursor() {
    cursorTexture.loadFromFile(resource("cursors.png"));
#ifdef STEALTH_GRAPHIC_DEBUG
    font.loadFromFile(resource("fonts/OpenSans-Regular.ttf"));
#endif
}

void GameCursor::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Sprite cursor;
    cursor.setTexture(cursorTexture);
    cursor.setTextureRect(sf::IntRect(0, 96, 96, 96));
    cursor.setPosition(position);
    cursor.setScale(sf::Vector2f(1, 1));
    target.draw(cursor);

#ifdef STEALTH_GRAPHIC_DEBUG
    sf::Text txt;
    txt.setFont(font);
    std::stringstream coord;
    coord << position.x << ", " << position.y;
    txt.setString(coord.str());
    txt.setPosition(position.x + 10, position.y + 15);
    txt.setScale(0.5, 0.5);

    sf::FloatRect r = txt.getGlobalBounds();
    sf::RectangleShape re({r.width + 4,r.height + 4});
    re.setPosition({r.left - 2, r.top - 2});
    re.setFillColor(sf::Color(0, 0, 0, 127));

    target.draw(re);
    target.draw(txt);
#endif
}

void GameCursor::update(sf::RenderWindow &window) {
    position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}
