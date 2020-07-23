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
#include "PointedElement.hpp"
class GameCursor : public sf::Drawable, public sf::Transformable {
public:
    GameCursor();

    void update(sf::RenderWindow &window, const std::list<std::shared_ptr<Object>> &objects, const std::forward_list<std::shared_ptr<Enemy>> &enemies);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Texture cursorTexture;
    sf::Vector2f position;

#ifdef STEALTH_GRAPHIC_DEBUG
    sf::Font font;
    PointedElement pointedElement;
    int spriteX;
    int spriteY;
#endif
};


#endif //STEALTH_GAMECURSOR_HPP
