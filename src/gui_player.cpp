//
// Created by per on 21.04.2020.
//
#include <SFML/Graphics.hpp>
#include <iostream>

#include "gui.h"
#include "player.h"
#include "game.h"
#include "gui_player.h"


gui_player::gui_player(gui &_gui, player *_player):
_player(_player),
_gui(_gui),
textureMap(),
mouseCursor(),
territory(),
sprites()
{
    // Draw territory
    territory.setPosition(sf::Vector2f(
            _player->_territory[0] * _gui.tileRatioWidth,
            _player->_territory[1] * _gui.tileRatioHeight
            ));

    territory.setSize(sf::Vector2f(
            _player->_territory[2] * _gui.tileRatioWidth,
            _player->_territory[3] * _gui.tileRatioHeight
            ));
    mouseCursor.setFillColor(sf::Color(0, 0, 255 * (_player->id / 4), 128));

    // Draw cursor
    mouseCursor.setSize(sf::Vector2f(
            _gui.tileRatioWidth,
            _gui.tileRatioHeight
            ));




    std::map<Constants::Entity, std::string> textures = {
            {Constants::Entity::MILITIA, "resources/sprites/units/militia.png"},
            {Constants::Entity::GRUNT, "resources/sprites/units/grunt.png"},
            {Constants::Entity::FOOTMAN, "resources/sprites/units/footman.png"},
            {Constants::Entity::ARMORED_GRUNT, "resources/sprites/units/armored_grunt.png"},
            {Constants::Entity::BASIC_TOWER, "resources/sprites/buildings/tower_1.png"},
            {Constants::Entity::FAST_TOWER, "resources/sprites/buildings/tower_2.png"},
            {Constants::Entity::FASTER_TOWER, "resources/sprites/buildings/lazer_tower.png"},
            //{Constants::Entity::AR, "resources/sprites/units/archer_den.png"},
            //{Constants::Entity::MILITIA, "resources/sprites/units/sun_altar.png"},
            //{Constants::Entity::MILITIA, "resources/sprites/units/spike_machine.png"},
            //{Constants::Entity::MILITIA, "resources/sprites/units/slow_tower.png"},
            //{Constants::Entity::MILITIA, "resources/sprites/units/rootslinger.png"}
    };
    for(auto &item: textures){
        textureMap[item.first] = getTexture(item.second);
    }

}

sf::Texture gui_player::getTexture(std::string &path) const{

    auto f = this->_gui._game.fs.open(path);
    sf::Texture texture;
    texture.loadFromMemory(f.begin(), f.size());
    return texture;
}

void gui_player::setup(){

}

void gui_player::updateColor(){
    auto progress =  (_player->health / (float)_player->_game._c.startHealth );
    //std::cout << progress << std::endl;
    if(progress < 0){
        std::cout << _player->health << std::endl;
    }
    sf::Color c = sf::Color(255 * (1 - progress), 255 * (progress), 0);
    territory.setFillColor(c);

}

void gui_player::reset() {
    updateColor();
    updateCursor();
    sprites.clear();

}

void gui_player::updateCursor() {
    mouseCursor.setPosition(
            _player->mouse.x * _gui.tileRatioWidth,
            _player->mouse.y * _gui.tileRatioHeight
            );
}
