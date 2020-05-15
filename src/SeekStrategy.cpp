//
// Created by vivedo on 09/05/20.
//

#include "SeekStrategy.hpp"

void SeekStrategy::addLocation(sf::Vector2i location) {
    locations.push_back(location);
}

sf::Vector2f SeekStrategy::getNextMove(GameObject &gameObject, Game &game) {

    sf::Vector2f nextMove;

    if (locations.size() != 0) {
        if ((gameObject.position.x / game.map->getTileSize().x) ==
            (locations.at(currentTarget).x / game.map->getTileSize().x) &&
            (gameObject.position.y / game.map->getTileSize().y) ==
            (locations.at(currentTarget).y / game.map->getTileSize().y)) {

            std::cout << "Arrived To {x = " << gameObject.position.x / game.map->getTileSize().x << "} y = { "
                      << gameObject.position.y / game.map->getTileSize().x << std::endl;
            currentTarget++;
            currentTarget = currentTarget % locations.size();
            std::cout << "Go To {x = " << locations.at(currentTarget).x << "} y = { " << locations.at(currentTarget).y
                      << std::endl;
        }

        aStar = new AStar(game.objects, game.map->getMapSize(), game.map->getTileSize());

        Node from = {gameObject.position.x, gameObject.position.y};
        Node to = {locations.at(currentTarget).x, locations.at(currentTarget).y};


        std::vector<Node> path = aStar->getPath(from, to);
        Node next = path.at(1);

        if (!path.empty()) {
            int tileOffsetX = (game.map->getTileSize().x + 1);
            int tileOffsetY = (game.map->getTileSize().y + 1);
            nextMove.x = (static_cast<float>(next.x * game.map->getTileSize().x) - from.x) < 0 ? -tileOffsetX : tileOffsetX;
            nextMove.y = (static_cast<float>(next.y * game.map->getTileSize().y) - from.y) < 0 ? -tileOffsetY : tileOffsetY;
            return nextMove;
        }


    }
}


