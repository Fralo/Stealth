//
// Created by leonardo on 14/05/20.
//

#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch.hpp>
#include "../src/Astar.hpp"

TEST_CASE("Pathfinding without obstacles", "[A*]") {
    std::forward_list<sf::IntRect> obstacles;
    Vector2u8 mapSize(30, 30);

    auto&& astar2 = new Astar(obstacles, mapSize);
    auto&& path = astar2->getPath({0, 0}, {29, 29});

    /*
     * Require existing path
     */
    REQUIRE( path != nullptr );

    /*
     * Require path size 30 as it is best path (straight diagonal path)
     */
    REQUIRE( std::distance(path->begin(), path->end()) == 30 );

    BENCHMARK("AStar::getPath") {
        return  astar2->getPath({0, 0}, {29, 29});
    };
}

TEST_CASE("Pathfinding without obstacles, from and to coincide", "[A*]") {
    std::forward_list<sf::IntRect> obstacles;
    Vector2u8 mapSize(30, 30);

    auto&& astar2 = new Astar(obstacles, mapSize);
    auto&& path = astar2->getPath({15, 15}, {15, 15});

    /*
     * Require existing path
     */
    REQUIRE( path != nullptr );

    /*
     * Require path size 1
     */
    REQUIRE( std::distance(path->begin(), path->end()) == 1 );

    BENCHMARK("AStar::getPath") {
        return  astar2->getPath({15, 15}, {15, 15});
    };
}

TEST_CASE("Pathfinding with obstacles, known existing path", "[A*]") {
    std::forward_list<sf::IntRect> obstacles;
    obstacles.push_front({0, 10, 29, 1});
    obstacles.push_front({1, 20, 29, 1});

    Vector2u8 mapSize(30, 30);

    auto&& astar2 = new Astar(obstacles, mapSize);
    auto&& path = astar2->getPath({0, 0}, {29, 29});

    /*
     * Require existing path
     */
    REQUIRE( path != nullptr );

    BENCHMARK("AStar::getPath") {
        return  astar2->getPath({0, 0}, {29, 29});
    };
}

TEST_CASE("Pathfinding with obstacles, known no existing path", "[A*]") {
    std::forward_list<sf::IntRect> obstacles;
    obstacles.push_front({0, 10, 30, 1});
    obstacles.push_front({1, 20, 29, 1});

    Vector2u8 mapSize(30, 30);

    auto&& astar2 = new Astar(obstacles, mapSize);
    auto&& path = astar2->getPath({0, 0}, {29, 29});

    /*
     * Require non existing path
     */
    REQUIRE( path == nullptr );

    BENCHMARK("AStar::getPath") {
        return  astar2->getPath({0, 0}, {29, 29});
    };
}

TEST_CASE("Pathfinding with obstacles, destination is INSIDE an obstacle", "[A*]") {
    std::forward_list<sf::IntRect> obstacles;

    obstacles.push_front({29, 29, 1, 1});

    Vector2u8 mapSize(30, 30);

    auto&& astar2 = new Astar(obstacles, mapSize);
    auto&& path = astar2->getPath({0, 0}, {29, 29});

    /*
     * Require non existing path
     */
    REQUIRE( path == nullptr );

    BENCHMARK("AStar::getPath") {
        return  astar2->getPath({0, 0}, {29, 29});
    };
}

TEST_CASE("Pathfinding with obstacles, source is INSIDE an obstacle", "[A*]") {
    std::forward_list<sf::IntRect> obstacles;

    obstacles.push_front({0, 0, 2, 2});

    Vector2u8 mapSize(30, 30);

    auto&& astar2 = new Astar(obstacles, mapSize);
    auto&& path = astar2->getPath({0, 0}, {29, 29});

    /*
     * Require non existing path
     */
    REQUIRE( path == nullptr );

    BENCHMARK("AStar::getPath") {
        return  astar2->getPath({0, 0}, {29, 29});
    };
}