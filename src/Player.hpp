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
#include "Direction.hpp"
#include "MathHelper.hpp"

#define GRID_SCALE_FACTOR 16

class Player : public GameObject {
public:
    Player(sf::Vector2f position, Weapon weapon);

    void update(const std::list<std::shared_ptr<Object>> &objects, TiledMap &map);
    void applyDamage(int damage);
    void setTarget(std::shared_ptr<GameObject> target);
    void setTarget(sf::Vector2f next);
    void shootEnemy(std::shared_ptr<GameObject> enemy);
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Clock clock;
    Weapon weapon;
    sf::Vector2f nextPos;
    sf::Clock cacheTime;
    Path *path = nullptr;
    sf::SoundBuffer movingSfxBuffer;
    sf::Sound movingSfx;
    std::shared_ptr<GameObject> target;

};


#endif //STEALTH_PLAYER_HPP
