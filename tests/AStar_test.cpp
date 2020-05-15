//
// Created by leonardo on 14/05/20.
//

#include "../src/AStar.hpp"
#include <catch.hpp>


TEST_CASE("AStar algorithm", "[AStar]") {
    Node from{100,100}, to{400,400};
    std::list <Object*> *obs = new std::list<Object*>();
    sf::Vector2u mapSize = {32,32};
    sf::Vector2u tileDimension = {48,48};
    AStar* algo = new AStar(*obs, mapSize,tileDimension);
    std::vector<Node> path = algo->getPath(from, to);
    Node lastMove = path.at(path.size()-1);
    delete algo;
    INFO("Enemy should have reached player");
    CHECK( (lastMove.x == static_cast<int>(to.x/tileDimension.x)  && lastMove.y == static_cast<int>(to.y/tileDimension.x)) );


}
