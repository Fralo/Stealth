//
// Created by vivedo on 11/05/20.
//

#ifndef STEALTH_PLAYER_HPP
#define STEALTH_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameObject.hpp"
#include "Weapon.h"
#include "Astar.hpp"
#include "TiledMap.hpp"

#define GRID_SCALE_FACTOR 16

class Player : public GameObject {
public:
    Player(sf::Vector2f position, Weapon weapon);

    /*
     * TODO: remove GameObject::update(Game&)
     */
    void update(const std::list<Object*>& objects, TiledMap &map);
    void setNextPos(sf::Vector2f next);
    bool move;
    void applyDamage(int damage);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    Weapon weapon;
    sf::Vector2f nextPos;
    sf::Clock cacheTime;
    Path *path = nullptr;
    sf::SoundBuffer movingSfxBuffer;
    sf::Sound movingSfx;
};


#endif //STEALTH_PLAYER_HPP
