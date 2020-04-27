//
// Created by per on 21.04.2020.
//

#ifndef DEEPLINEWARS_GUI_PLAYER_H
#define DEEPLINEWARS_GUI_PLAYER_H
class player;
class gui;
class entity;
#include <map>
#include "constants.h"
#include <list>
#include "gui_entity.h"
#include <SFML/Graphics.hpp>

class gui_player {
public:
    player *_player;
    gui &_gui;
    sf::RectangleShape territory;
    sf::RectangleShape mouseCursor;
    std::map<int, sf::Texture> textureMap;
    std::map<int, gui_entity> sprites;
    explicit gui_player(gui &_gui, player *_player);

    void updateColor();

    void setup();

    void reset();

    void updateCursor();

    sf::Texture getTexture(std::string &path) const;
};


#endif //DEEPLINEWARS_GUI_PLAYER_H
