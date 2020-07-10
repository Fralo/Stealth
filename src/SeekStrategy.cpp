//
// Created by vivedo on 09/05/20.
//

#include "SeekStrategy.hpp"

void SeekStrategy::addLocation(sf::Vector2i location) {
    locations.emplace_back(location / GRID_SCALE_FACTOR);
}

sf::Vector2f SeekStrategy::getNextMove(GameObject &gameObject, const std::list<Object*> &objects,Player &player,TiledMap &map) {
    if (locations.empty())
        return {0, 0};

    auto position = Vector2u8(gameObject.getPos() / (float) GRID_SCALE_FACTOR);

    int elapsedCacheTime = cacheTime.getElapsedTime().asMilliseconds();

    /*
     * if path is nullptr (previous A* search did not found a route) wait 500ms before another search.
     * In every case refresh every 2s or when path is empty
     */
    if (path == nullptr && elapsedCacheTime > 500 || elapsedCacheTime > (2000) || (path != nullptr && path->empty())) {
        std::forward_list<sf::IntRect> obstacles;

        for (auto &&obj : objects) {
            auto cb = sf::IntRect(obj->tile->collisionBox);

            obstacles.push_front({static_cast<int>((obj->position.x + cb.left) / GRID_SCALE_FACTOR), static_cast<int>((obj->position.y + cb.top) / GRID_SCALE_FACTOR),
                                  static_cast<int>(std::ceil(((float) cb.width) / GRID_SCALE_FACTOR)), static_cast<int>(std::ceil(((float) cb.height) / GRID_SCALE_FACTOR))});
        }

        auto astar = new Astar(obstacles, sf::Vector2<uint8_t>(map.getMapActualSize() / (unsigned int) GRID_SCALE_FACTOR));
        path = astar->getPath(position, locations.at(currentTarget));

        cacheTime.restart();
    }

    if(path != nullptr && !path->empty()) {
        if (path->front() == position)
            path->pop_front();

        if (!path->empty()) {
            auto &&pNext = path->front();

            int dX = pNext.x - position.x;
            int dY = pNext.y - position.y;

            /*
             * make vector modulus 1
             */
            float scaler = 1.0f / (dX * dX + dY * dY);
            sf::Vector2f nextDirection = sf::Vector2f(dX * scaler, dY * scaler);

            return nextDirection;
        }

        currentTarget++;
        currentTarget %= locations.size();
        path = nullptr;
    }

    return {0, 0};
}


