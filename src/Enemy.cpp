//
// Created by vivedo on 09/05/20.
//

#include "Enemy.hpp"

Enemy::Enemy(Strategy &defaultStrategy, Weapon weapon) : defaultStrategy(&defaultStrategy), weapon(weapon) {

}

void Enemy::update(Game &game) {

}

void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states) const {

}
