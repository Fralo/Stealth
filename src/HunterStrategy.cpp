//
// Created by mattia on 14/05/20.
//

#include "HunterStrategy.hpp"

sf::Vector2f HunterStrategy::getNextMove(GameObject &gameObject, Game &game) {
    sf::Vector2f nextMove;
    aStar = new AStar(game.objects, game.map->getMapSize(), game.map->getTileSize());

    Node from = {gameObject.position.x, gameObject.position.y};
    Node to = {game.player->position.x,game.player->position.y};

    std::vector<Node> path = aStar->getPath(from, to);
    Node next = path.at(1);

    if (!path.empty()) {
        nextMove.x = float(next.x * game.map->getTileSize().x) - from.x;
        nextMove.y = float(next.y * game.map->getTileSize().y) - from.y;
    }

    return nextMove;
}
