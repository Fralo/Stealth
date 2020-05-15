//
// Created by vivedo on 15/05/20.
//

#include <iostream>
#include <catch.hpp>
#include <SFML/Graphics.hpp>
#include "../src/AStar2.hpp"

TEST_CASE("AStar2 algorithm drawing", "[AStar2]") {

    std::list<sf::IntRect> obstacles;

    /**/
    obstacles.push_front({5, 0, 1, 28});
    obstacles.push_front({20, 0, 2, 20});
    obstacles.push_front({12, 2, 1, 28});
    obstacles.push_front({14, 14, 8, 3});
    /**/

    sf::Vector2u mapSize(30, 30);

    sf::Vector2<unsigned char> from = {0, 0};
    sf::Vector2<unsigned char> to = {22, 2};

    auto&& astar2 = new AStar2(obstacles, mapSize);

    std::cout << "getting path" << std::endl;

    auto&& path = astar2->getPath(from, to);

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
    else {
        for(auto&& node : *path) {
            // std::cout << (int)node.x << ":" << (int)node.y << std::endl;
            grid[node.y][node.x] = '*';
        }

        std::cout << "path length: " << path->size() << std::endl;

        auto&& first = path->front();

        std::cout << "first: " << (int) first.x << ":" << (int) first.y <<  std::endl;
    }

    grid[from.y][from.x] = 'F';
    grid[to.y][to.x] = 'T';

    for(auto & y : grid) {
        for(char x : y)
            std::cout << x << " ";

        std::cout << std::endl;
    }

}