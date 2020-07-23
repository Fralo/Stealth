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
    PLAYER
};

struct PointedElement {
    Pointing pointedElementType;
    std::shared_ptr<GameObject> pointedElementObject;
};
class GameCursor : public sf::Drawable, public sf::Transformable {
public:
    GameCursor();

    void update(sf::RenderWindow &window, const std::list<std::shared_ptr<Object>> &objects, const std::forward_list<std::shared_ptr<Enemy>> &enemies);
    PointedElement getPointedElement();
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Texture cursorTexture;
    sf::Vector2f position;

    PointedElement pointedElement;
    int spriteX;
    int spriteY;

#ifdef STEALTH_GRAPHIC_DEBUG
    sf::Font font;
#endif
};


#endif //STEALTH_GAMECURSOR_HPP
