//
// Created by vivedo on 17/07/20.
//

#include "Animation.hpp"

void Animation::addFrame(std::shared_ptr<Tile> frame) {
    frames.push_back(frame);
}

std::shared_ptr<Tile> Animation::getCurrentFrame() {
    if (frames.empty())
        return nullptr;

    return frames.at((clk.getElapsedTime().asMilliseconds() / frameDuration) % frames.size());
}
