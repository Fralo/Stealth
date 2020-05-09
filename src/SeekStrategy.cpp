//
// Created by vivedo on 09/05/20.
//

#include "SeekStrategy.hpp"

sf::Vector2f SeekStrategy::getNextMove(GameObject &gameObject) {
    return sf::Vector2f();
}

SeekStrategy::SeekStrategy(int x, int y, int o, std::forward_list<sf::Vector2i> &l): locations(&l), x(x), y(y) {

}
