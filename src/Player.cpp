//
// Created by vivedo on 11/05/20.
//

#include "Player.hpp"

Player::Player(sf::Vector2f position, Weapon weapon) : weapon(weapon) {
    this->position = position;
    this->nextPos = position;

    movingSfxBuffer.loadFromFile("../res/music/yes_commander.ogg");
    movingSfx.setBuffer(movingSfxBuffer);
}

void Player::update(Game &game) {

    auto scaledPos = Vector2u8(position / (float) GRID_SCALE_FACTOR);
    auto scaledTargetPos = Vector2u8(nextPos / (float) GRID_SCALE_FACTOR);

    int elapsedCacheTime = cacheTime.getElapsedTime().asMilliseconds();

    /*
     * if path is nullptr (previous A* search did not found a route) wait 500ms before another search.
     * In every case refresh every 2s or when path is empty
     */
    if (path == nullptr && elapsedCacheTime > 500 || elapsedCacheTime > (2000) || (path != nullptr && path->empty())) {
        std::forward_list<sf::IntRect> obstacles;

        for (auto &&obj : game.objects) {
            auto cb = sf::IntRect(obj->tile.collisionBox);

            obstacles.push_front({static_cast<int>((obj->position.x + cb.left) / GRID_SCALE_FACTOR), static_cast<int>((obj->position.y + cb.top) / GRID_SCALE_FACTOR),
                                  static_cast<int>(std::ceil(((float) cb.width) / GRID_SCALE_FACTOR)), static_cast<int>(std::ceil(((float) cb.height) / GRID_SCALE_FACTOR))});
        }

        auto astar = new Astar(obstacles, Vector2u8(game.map->getMapActualSize() / (unsigned int) GRID_SCALE_FACTOR));

        path = astar->getPath(scaledPos, scaledTargetPos);

        cacheTime.restart();
    }

    if(path != nullptr && !path->empty()) {
        if (path->front() == scaledPos)
            path->pop_front();

        if (!path->empty()) {
            auto &&pNext = path->front();

            int dX = pNext.x - scaledPos.x;
            int dY = pNext.y - scaledPos.y;

            /*
             * make vector modulus 1
             */
            float scaler = 1.0f / (dX * dX + dY * dY);
            sf::Vector2f next = sf::Vector2f(dX * scaler, dY * scaler);

            float movementFactor = 3;
            position = sf::Vector2f(position.x + next.x * movementFactor, position.y + next.y * movementFactor);
        }
    }
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    sf::RectangleShape liferect({100,20});
    sf::CircleShape enemyShape(10);

    liferect.setFillColor(sf::Color(0,200,0));
    enemyShape.setFillColor(sf::Color(200, 0, 0));

    liferect.setPosition(target.getView().getCenter().x - 380,target.getView().getCenter().y + 260);
    enemyShape.setPosition(position.x, position.y);

    target.draw(liferect);
    target.draw(enemyShape);

}

void Player::setNextPos(sf::Vector2f next) {
    nextPos = next;
    movingSfx.play();
}