//
// Created by per on 22.04.2020.
//

#include "gui_entity.h"
#include "gui_player.h"
#include "gui.h"
#include "game.h"
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "player.h"
#include <iostream>

gui_entity::gui_entity(gui_player& _player, entity &_entity):
_player(_player),
_entity(_entity),
texture(_player.textureMap.at(_entity.entityID)),
sprite(texture)
{

    auto &movement = _entity._player->_movement;
    auto size = texture.getSize();
    sprite.setOrigin({ (movement.first == 1) ? 0 : sprite.getLocalBounds().width, 0 });
    sprite.setScale(
            movement.first * (_player._gui.tileRatioWidth /texture.getSize().x),
            _player._gui.tileRatioHeight / texture.getSize().y
            );

}

void gui_entity::updatePosition() {
    auto &movement = _entity._player->_movement;

    double progress = (_entity.tickMoveCounter / _player._player->_game._c.mechanics.tickEntityMove);
    float inter = (progress * _player._gui.tileRatioWidth) * movement.first;
    sprite.setPosition(
            (_entity.x * _player._gui.tileRatioWidth) + inter,
            _entity.y * _player._gui.tileRatioHeight
            );

}

void gui_entity::render(sf::RenderWindow &window){
    if(_entity.spawned){
        window.draw(sprite);
    }

}
