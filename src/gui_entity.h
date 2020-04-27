//
// Created by per on 22.04.2020.
//

#ifndef DEEPLINEWARS_GUI_ENTITY_H
#define DEEPLINEWARS_GUI_ENTITY_H
#include <SFML/Graphics.hpp>
class entity;
class gui_player;
class gui_entity {

public:
    gui_player& _player;
    entity &_entity;
    sf::Texture texture;
    sf::Sprite sprite;

    explicit gui_entity(gui_player& _player, entity &_entity);
    void updatePosition();

    void render(sf::RenderWindow &window);

    bool spawned = false;
};


#endif //DEEPLINEWARS_GUI_ENTITY_H
