//
// Created by per on 23.04.2020.
//
#include "game.h"
#include "player.h"
#include "virtual_mouse.h"
#include "cmath"

void virtual_mouse::setPosition(double _x, double _y) {
    if(0.0 > x > 1.0 || 0.0 > y > 1.0){
        throw std::runtime_error("Fractional mouse position must be set within 0.0->1.0 bounds");
    }

    x = maxX * _x;
    y = maxY * _y;
}

void virtual_mouse::setPosition(int _x, int _y) {
    x = _x;
    y = _y;
}

virtual_mouse::virtual_mouse(player &_player):
maxX(_player._game.width - 1),
maxY(_player._game.height - 1),
_player(_player)
{

    // Default mouse location to middle of territory side.
    if(_player._movement.first == 1 && _player._movement.second == 0){
        // Left to Right Movement
        x = ceil(maxX / 4.0);
        y = ceil(maxY / 2.0);
    } else if(_player._movement.first == -1 && _player._movement.second == 0){
        // right to left Movement
        x = maxX - (int)ceil(maxX / 4.0);
        y = ceil(maxY / 2.0);
    }else{
        throw std::runtime_error("Mouse movement not implemented for other than player 1 and 2.");
    }


    _player._game._emitter.emit(Constants::MOUSE_MOVE, _player.id);
}

bool virtual_mouse::moveLeft() {
    x = std::max(0, x - 1);
    _player._game._emitter.emit(Constants::MOUSE_MOVE, _player.id);
    return true;
}

bool virtual_mouse::moveRight() {
    x = std::min(maxX - 1, x + 1);
    _player._game._emitter.emit(Constants::MOUSE_MOVE, _player.id);
    return true;
}

bool virtual_mouse::moveUp() {
    y = std::max(0, y - 1);
    _player._game._emitter.emit(Constants::MOUSE_MOVE, _player.id);
    return true;
}

bool virtual_mouse::moveDown() {
    y = std::min(maxY - 1, y + 1);
    _player._game._emitter.emit(Constants::MOUSE_MOVE, _player.id);
    return true;
}

virtual_mouse::virtual_mouse(player &_player, bool):
_player(_player){

}
