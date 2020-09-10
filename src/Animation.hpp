//
// Created by vivedo on 17/07/20.
//

#ifndef STEALTH_ANIMATION_HPP
#define STEALTH_ANIMATION_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "Tile.hpp"

class Animation {
public:
    void addFrame(std::shared_ptr<Tile> frame);

    std::shared_ptr<Tile> getCurrentFrame();

private:
    std::vector<std::shared_ptr<Tile>> frames;
    sf::Clock clk;
    int frameDuration = 100;
};


#endif //STEALTH_ANIMATION_HPP
