//
// Created by vivedo on 13/05/20.
//

#ifndef STEALTH_GAMECURSOR_HPP
#define STEALTH_GAMECURSOR_HPP

#include "cfg.hpp"
#include <SFML/Graphics.hpp>
#include <sstream>
#include "GameObject.hpp"
#include "Object.hpp"
#include "macro.h"
#include "Enemy.hpp"
#include <list>

enum Pointing{
    NOTHING,
    ENEMY,
    OBSTACLE,
    ITEM,
    PLAYER
};

struct PointedElement {
    Pointing pointedElementType;
    std::shared_ptr<GameObject> pointedElementObject;
};
class GameCursor : public sf::Drawable, public sf::Transformable {
public:
    GameCursor();

    void update(sf::RenderWindow &window, const std::list<std::shared_ptr<Object>> &objects, const std::forward_list<std::shared_ptr<Enemy>> &enemies, const std::shared_ptr<Player> &player);
    PointedElement getPointedElement();
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Texture cursorTexture;
    sf::Vector2f position;

    PointedElement pointedElement;
    sf::Vector2i spriteCoord;
    sf::Vector2i shootCursor = {0, 0};
    sf::Vector2i denyCursor = {192,0};
    sf::Vector2i grabCursor = {96,0};
    sf::Vector2i normalCursor = {0,96};

    sf::Vector2i spriteDimesion = {96,96};
#ifdef STEALTH_GRAPHIC_DEBUG
    sf::Font font;
#endif
};


#endif //STEALTH_GAMECURSOR_HPP
