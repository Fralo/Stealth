//
// Created by vivedo on 13/05/20.
//

#include "GameCursor.hpp"

GameCursor::GameCursor() {
    cursorTexture.loadFromFile(resource("cursors.png"));
    spriteCoord = normalCursor;
    pointedElement.pointedElementType = NOTHING;
    pointedElement.pointedElementObject = nullptr;
#ifdef STEALTH_GRAPHIC_DEBUG
    font.loadFromFile(resource("fonts/OpenSans-Regular.ttf"));
#endif
}

void GameCursor::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Sprite cursor;
    cursor.setTexture(cursorTexture);


    cursor.setTextureRect(sf::IntRect(spriteCoord.x, spriteCoord.y, spriteDimesion.x,spriteDimesion.y));
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

void GameCursor::update(sf::RenderWindow &window, const std::list<std::shared_ptr<Object>> &objects,
                        const std::forward_list<std::shared_ptr<Enemy>> &enemies,
                        const std::shared_ptr<Player> &player) {
    position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    pointedElement.pointedElementType = NOTHING;
    pointedElement.pointedElementObject = nullptr;
    spriteCoord = normalCursor;
    //check if the player can shot the enemy
    for (const std::shared_ptr<Enemy> &enemy : enemies) {
        if (abs(position.x - enemy->getPos().x) < 10 && abs(position.y - enemy->getPos().y) < 10 &&
            MathHelper::distanceBetweenTwoPoints(player->getPos(), enemy->getPos()) < player->getWeapon().distanceOfUse) {
            spriteCoord = shootCursor;
            pointedElement.pointedElementType = ENEMY;
            pointedElement.pointedElementObject = enemy;
            break;
        }
    }
    //check if the player can shot the enemy
    for (const std::shared_ptr<Object> &obs : objects) {
        if (obs->getAbsCollisionBox().contains(position.x, position.y)) {
            if (!obs->properties.collectible) {
                spriteCoord = denyCursor;
                pointedElement.pointedElementType = OBSTACLE;
                pointedElement.pointedElementObject = obs;
                break;
            } else {
                spriteCoord = grabCursor;
                pointedElement.pointedElementType = ITEM;
                pointedElement.pointedElementObject = obs;
            }
        }
    }
}

PointedElement GameCursor::getPointedElement() {
    return this->pointedElement;
}
