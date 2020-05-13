//
// Created by vivedo on 13/05/20.
//

#ifndef STEALTH_GAMECURSOR_HPP
#define STEALTH_GAMECURSOR_HPP

#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "macro.h"

class GameCursor : public sf::Drawable, public sf::Transformable {
public:
    GameCursor();

    void update(Game &game, sf::Window &window);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Texture cursorTexture;
    sf::Vector2i position;
};


#endif //STEALTH_GAMECURSOR_HPP
