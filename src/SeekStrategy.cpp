//
// Created by vivedo on 09/05/20.
//

#include "SeekStrategy.hpp"

void SeekStrategy::addLocation(sf::Vector2i location) {
    locations.push_back(location);
}

sf::Vector2f SeekStrategy::getNextMove(GameObject &gameObject, Game &game) {

sf::Vector2f nextMove;

if(locations.size() != 0) {
    aStar = new AStar(game.obstacles, game.map.getMapSize(), game.map.getTileSize());

    Node from = {gameObject.position.x, gameObject.position.y};
    Node to = {locations.at(currentTarget).x,locations.at(currentTarget).y};

    std::vector<Node> path = aStar->getPath(from, to);
    Node next = path.at(1);

    if (!path.empty()) {
        nextMove.x = float(next.x * game.map.getTileSize().x) - from.x;
        nextMove.y = float(next.y * game.map.getTileSize().y) - from.y;
    }

    if (next.x == (to.x/game.map.getTileSize().x) && next.y == (to.y/game.map.getTileSize().y)) {

        std::cout<<"Location n. "<<currentTarget<<std::endl;
        std::cout<<"Arrived to : { x = " <<to.x<< " y = "<<to.y<<"}"<<std::endl;
        currentTarget++;
        currentTarget = currentTarget % locations.size();


    }
    return nextMove;
}
    //std::cout << nextMove.x <<" " << nextMove.y <<std::endl;


}


