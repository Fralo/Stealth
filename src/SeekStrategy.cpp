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

    aStar = new AStar(game.obstacles, game.map.getMapSize(), game.map.getTileSize());

    Node from = {gameObject.position.x, gameObject.position.y};
    Node to{1200,1200};
    /*
    //set the current target
    i = 0;
    for (auto location : locations) {
        if(i == currentTarget) {
            to.x = location.x;
            to.y = location.y;
        }
        i++;
    }
    */
    std::vector<Node> path =  aStar->getPath(from,to);
    Node next = path.at(1);

/* TODO spiegare a fralo che è sta roba
    if(isArrivedToTarget(next,to)) {
        currentTarget++;
        currentTarget = currentTarget % nLocation;
    }
*/
    sf::Vector2f nextMove;

    if(!path.empty()) {
        //TODO FRITX TI ODIO
        nextMove.x = next.x;
        nextMove.y = next.y;
    }
    std::cout << nextMove.x <<" " << nextMove.y <<std::endl;
    return nextMove;


    //return sf::Vector2f();
}

bool SeekStrategy::isArrivedToTarget(Node check, Node target) {
    return check.y == target.y && check.x == target.x;
}

