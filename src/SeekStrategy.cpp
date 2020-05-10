//
// Created by vivedo on 09/05/20.
//

#include "SeekStrategy.hpp"

sf::Vector2f SeekStrategy::getNextMove(GameObject &gameObject) {

    //TODO: set the map by the gameObject method getMap

    //TODO: make a loop to change the target of a star when the enemy was arrived to oe of the default position

    Node from;
    from.x = gameObject.x;
    from.y = gameObject.y;
    Node to;

    std::vector<Node> path =  aStar->getPath(from,to);

    //return sf::Vector2f();
}

SeekStrategy::SeekStrategy(int x, int y, int o, std::forward_list<sf::Vector2i> &l): locations(&l), x(x), y(y) {
    nLocation = l.max_size();
}

