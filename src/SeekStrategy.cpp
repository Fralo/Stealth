//
// Created by vivedo on 09/05/20.
//

#include "SeekStrategy.hpp"

void SeekStrategy::addLocation(sf::Vector2i location) {
    locations.push_back(location);
}

sf::Vector2f SeekStrategy::getNextMove(GameObject &gameObject, Game &game) {

    int i = 0;
    for(auto it = locations.begin(); it != locations.end(); ++it)
        i++;
    nLocation = i;

    aStar = new AStar(game.obstacles, game.map.getMapSize());

    Node from = {gameObject.position.x, gameObject.position.y};
    Node to{};

    //set the current target
    i = 0;
    for (auto location : locations) {
        if(i == currentTarget) {
            to.x = location.x;
            to.y = location.y;
        }
        i++;
    }

    std::vector<Node> path =  aStar->getPath(from,to);

    Node current, next;
    int pass = 0;
    for(Node a : path) {
        if(pass == 0) current = a;
        if(pass++ == 1) next = a;
    }

    if(isArrivedToTarget(next,to)) {
        currentTarget++;
        currentTarget = currentTarget % nLocation;
    }

    sf::Vector2f nextMove;

    if(!path.empty()) {
        sf::Vector2f nextMove;
        nextMove.x = next.x;
        nextMove.y = next.y;
    }

    return nextMove;


    //return sf::Vector2f();
}

bool SeekStrategy::isArrivedToTarget(Node check, Node target) {
    return check.y == target.y && check.x == target.x;
}

