//
// Created by vivedo on 11/05/20.
//

#include "Player.hpp"

Player::Player(sf::Vector2f position, Weapon weapon) : weapon(weapon) {
    setPos(position);
    this->nextPos = position;

    movingSfxBuffer.loadFromFile("../res/music/yes_commander.ogg");
    movingSfx.setBuffer(movingSfxBuffer);
}

void Player::update(const std::list<std::shared_ptr<Object>>& objects, TiledMap &map) {
    auto scaledPos = Vector2u8(getPos() / (float) GRID_SCALE_FACTOR);
    auto scaledTargetPos = Vector2u8(nextPos / (float) GRID_SCALE_FACTOR);

    int elapsedCacheTime = cacheTime.getElapsedTime().asMilliseconds();

    /*
     * if path is nullptr (previous A* search did not found a route) wait 500ms before another search.
     * In every case refresh every 2s or when path is empty
     */
    if (path == nullptr && elapsedCacheTime > 500 || elapsedCacheTime > (2000) || (path != nullptr && path->empty())) {
        std::forward_list<sf::IntRect> obstacles;

        for (auto &&obj : objects) {
            auto cb = sf::IntRect(obj->tile->collisionBox);

            obstacles.push_front({static_cast<int>(std::floor((obj->getPos().x + cb.left) / GRID_SCALE_FACTOR)), static_cast<int>(std::floor((obj->getPos().y + cb.top) / GRID_SCALE_FACTOR)),
                                  static_cast<int>(std::ceil(((float) cb.width) / GRID_SCALE_FACTOR)), static_cast<int>(std::ceil(((float) cb.height) / GRID_SCALE_FACTOR))});
        }

        auto astar = new Astar(obstacles, Vector2u8(map.getMapActualSize() / (unsigned int) GRID_SCALE_FACTOR));

        path = astar->getPath(scaledPos, scaledTargetPos);

        cacheTime.restart();
    }

    // TODO: refine orientation detection methods
    sf::Vector2f *next = nullptr;

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
            next = new sf::Vector2f(dX * scaler, dY * scaler);

            float movementFactor = 3;
            setPos(sf::Vector2f(getPos().x + next->x * movementFactor, getPos().y + next->y * movementFactor));
        }
    }

    const char *dir = "idle";
    if(next != nullptr)
        switch(Direction(*next)){
            case Direction::NORTH:
                dir = "walk_n";
                break;
            case Direction::NORTH_EAST:
                dir = "walk_ne";
                break;
            case Direction::EAST:
                dir = "walk_e";
                break;
            case Direction::SUD_EAST:
                dir = "walk_se";
                break;
            case Direction::SUD:
                dir = "walk_s";
                break;
            case Direction::SUD_OVEST:
                dir = "walk_so";
                break;
            case Direction::OVEST:
                dir = "walk_o";
                break;
            case Direction::NORTH_OVEST:
                dir = "walk_no";
                break;
        }

    tile = map.getAnimation("player", dir).getCurrentFrame();
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // health bar
    sf::RectangleShape liferect({static_cast<float>(getHealth()),20});
    liferect.setFillColor(sf::Color(0,200,0));
    liferect.setPosition(target.getView().getCenter().x - 380,target.getView().getCenter().y + 260);
    target.draw(liferect);

    tile->setPosition(getPos().x - 30, getPos().y - 30);
    target.draw(*tile);
}

void Player::setTarget(sf::Vector2f next) {
    nextPos = next;
    movingSfx.play();
    target = nullptr;
}
void Player::setTarget(std::shared_ptr<GameObject> target) {
    Player::target = target;
}

void Player::applyDamage(int damage) {
    setHealth(std::max(health - damage, 0u));
}



