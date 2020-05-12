//
// Created by vivedo on 09/05/20.
//

#include "SeekStrategy.hpp"

sf::Vector2f SeekStrategy::getNextMove(GameObject &gameObject) {

    Node from;
    from.x = gameObject.position.x;
    from.y = gameObject.position.y;
    Node to;

    //set the current target
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

    //TODO: find the currect nextmove in the path

    Node nextMove;

    if(isArrivedToTarget(nextMove,to))
    {
        currentTarget++;
        currentTarget = currentTarget % nLocation;
    }

    //TODO: put the node into a vector 2i and return


    //return sf::Vector2f();
}

SeekStrategy::SeekStrategy(int x, int y, int o, std::forward_list<sf::Vector2i> &l, std::forward_list<Obstacle> &obs): locations(&l), x(x), y(y) {

    int i = 0;
    for ( auto it = l.begin(); it != l.end(); ++it )
        i++;
    nLocation = i;
    aStar = new AStar(obs);
}

bool SeekStrategy::isArrivedToTarget(Node check, Node target) {
    if(check.y == target.y && check.x == target.x)
        return true;
    else
        return false;
}

