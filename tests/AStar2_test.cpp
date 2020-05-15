//
// Created by vivedo on 15/05/20.
//

#include <iostream>
#include <catch.hpp>
#include <SFML/Graphics.hpp>
#include "../src/AStar2.hpp"

TEST_CASE("AStar2 algorithm", "[AStar2]") {

    std::list<sf::IntRect> obstacles;

    obstacles.push_front({5, 0, 4, 20});

    obstacles.push_front({20, 5, 4, 30});

    sf::Vector2u mapSize(30, 30);

    auto&& astar2 = new AStar2(obstacles, mapSize);
    auto&& path = astar2->getPath({0, 0}, {27, 20});

    char grid[30][30];

    for(auto & x : grid)
        for(char & y : x)
            y = ' ';

    for(sf::IntRect obs : obstacles) {
        for(int x = 0; x < obs.width; x++)
            for(int y = 0; y < obs.height; y++)
                grid[y + obs.top][x + obs.left] = 'O';
    }

    if(path == nullptr)
        std::cout << "path null" << std::endl;
    else
        for(auto&& node : *path) {
            std::cout << node.x << ":" << node.y << std::endl;
            grid[node.y][node.x] = '*';
        }

    for(auto & y : grid) {
        for(char x : y)
            std::cout << x << " ";

        std::cout << std::endl;
    }

}