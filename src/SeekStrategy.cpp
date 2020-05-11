//
// Created by vivedo on 09/05/20.
//

#include "SeekStrategy.hpp"

sf::Vector2f SeekStrategy::getNextMove(GameObject &gameObject) {

    //TODO: set the map by the gameObject method getMap


    Node from;
    from.x = gameObject.position.x;
    from.y = gameObject.position.y;
    Node to;

    int i = 0;
    for ( auto it = locations->begin(); it != locations->end(); ++it )
    {
        if(i == currentTarget)
        {
            to.x = it->x;
            to.y = it->y;
        }
        i++;
    }

    std::vector<Node> path =  aStar->getPath(from,to);
    Node nextMove;

    if(isArrivedToTarget(nextMove,to))
    {
        currentTarget++;
        currentTarget = currentTarget % nLocation;
    }

    //return sf::Vector2f();
}

SeekStrategy::SeekStrategy(int x, int y, int o, std::forward_list<sf::Vector2i> &l): locations(&l), x(x), y(y) {

    int i = 0;
    for ( auto it = l.begin(); it != l.end(); ++it )
        i++;
    nLocation =i;
}

bool SeekStrategy::isArrivedToTarget(Node check, Node target) {
    if(check.y == target.y && check.x == target.x)
        return true;
    else
        return false;
}

