//
// Created by vivedo on 11/05/20.
//

#include "Player.hpp"

void Player::update(Game &game) {
    Node from = {position.x, position.y};
    Node to = {nextPos.x, nextPos.y};
    if (!((from.x / game.map->getTileSize().x) ==
        (to.x / game.map->getTileSize().x) &&
        (from.y / game.map->getTileSize().y) ==
        (to.y / game.map->getTileSize().y)) && this->move) {
        sf::Vector2f nextMove;
        nextMove.x = 0;
        nextMove.y = 0;
        std::vector<Node> path = game.mainAStar->getPath(from, to);
        Node next = path.at(1);

        if (!path.empty()) {
            int tileOffsetX = (game.map->getTileSize().x + 1);
            int tileOffsetY = (game.map->getTileSize().y + 1);
            nextMove.x =
                    (static_cast<float>(next.x * game.map->getTileSize().x) - from.x) < 0 ? -tileOffsetX : tileOffsetX;
            nextMove.y =
                    (static_cast<float>(next.y * game.map->getTileSize().y) - from.y) < 0 ? -tileOffsetY : tileOffsetY;
        } else {
            sf::Vector2f nextMove;
            nextMove.x = 0;
            nextMove.y = 0;
        }


        float movementFactor = 0.05f;
        position = sf::Vector2i(position.x + nextMove.x * movementFactor, position.y + nextMove.y * movementFactor);
    }
    else {
        this->move = false;
    }
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::CircleShape enemyShape(10);
    enemyShape.setFillColor(sf::Color(200, 0, 0));
    enemyShape.setPosition(position.x, position.y);
    target.draw(enemyShape);
}

Player::Player(sf::Vector2i position, Weapon weapon) : weapon(weapon) {
    this->position = position;
    this->move = false;
    std::cout << "Created Player" << std::endl
              << "  Position " << std::endl
              << "     x: " << position.x << std::endl
              << "     y: " << position.y << std::endl
              << "  Weapon:" << std::endl
              << "     Rate:   " << weapon.rate << std::endl
              << "     Damage: " << weapon.damage << std::endl;
}

void Player::setNextPos(sf::Vector2i nextPos) {
    this->nextPos.x = nextPos.x;
    this->nextPos.y = nextPos.y;
}