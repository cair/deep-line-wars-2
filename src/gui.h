//
// Created by per on 20.04.2020.
//

#ifndef DEEPLINEWARS_GUI_H
#define DEEPLINEWARS_GUI_H
#include <SFML/Graphics.hpp>
#include "gui_player.h"
#include <map>

class game;
class gui {
public:

    int const width;
    int const height;
    float tileRatioWidth;
    float tileRatioHeight;
    std::map<int, gui_player*> playerMapping;
    std::vector<gui_player> guiPlayers;
    sf::VertexArray gridLines;
    game &_game;
    bool const enabled;
    sf::RenderWindow window;

    gui(int width, int height, game &g);

    void event();

    void render();

    void setupGrid();

    void reset();

    void setup();

    void setupEmitters();

    void updateUnitPosition(entity &_entity);

    void deleteUnit(entity &_entity);

    void addUnit(entity &_entity);
};


#endif //DEEPLINEWARS_GUI_H
