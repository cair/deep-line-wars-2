//
// Created by per on 17.04.2020.
//

#include "map.h"
#include "game.h"
#include <iostream>
#include "player.h"
#include "entity.h"

map::map(game& _game, int width, int height):
_game(_game),
width(width),
height(height),
state(width * height * Constants::NUM_LAYERS)
{
    //std::cout << width * height * Constants::NUM_LAYERS << std::endl;
    setup();


}

void map::setup() {
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            tiles.emplace_back(*this, x, y);
        }
    }

}

void map::reset(){
    for(auto &tile: tiles){
        tile.reset();
    }
}

bool map::_updatePosition(entity &_entity, int layer, int x, int y, bool sum) {
    int newPosition = toIndex(0, x, y);
    int oldIndex = toIndex(layer, _entity.x, _entity.y);
    int newIndex = toIndex(layer, x, y);

    // Remove from old location
    removeUnit(_entity);

    // Add to new location
    auto &newTile = tiles[newPosition];
    newTile._entities.try_emplace(_entity.id, &_entity);

    if(sum) {
        state[oldIndex] -= 1;
        state[newIndex] += 1;
        return  state[oldIndex] == 0;
    }else {
        state[oldIndex] = 0;
        state[newIndex] = 1;
    }

    _entity.x = x;
    _entity.y = y;


    return false;
}

void map::removeUnit(entity &_entity){
    // Remove from old location
    int position = toIndex(0, _entity.x, _entity.y);
    auto &tile = tiles[position];
    tile._entities.erase(_entity.id);

}

bool map::updatePosition(entity &_entity, const int x, const int y) {
    int layerID, layerCount;
    int playerLayer = _entity._player->_stateLayers[Constants::StateLayer::PLAYER_ID];
    if(_entity.category == Constants::EntityCategory::BUILDING){
        layerID = _entity._player->_stateLayers[Constants::StateLayer::BUILDING_ID];
        layerCount = _entity._player->_stateLayers[Constants::StateLayer::BUILDING_COUNT];
    } else if(_entity.category == Constants::EntityCategory::UNIT) {
        layerID = _entity._player->_stateLayers[Constants::StateLayer::UNIT_ID];
        layerCount = _entity._player->_stateLayers[Constants::StateLayer::UNIT_COUNT];
    }else{
        throw std::runtime_error("Illegal action.");
    }


    if(_updatePosition(_entity, layerCount, x, y, true))
    {
        _updatePosition(_entity, playerLayer, x, y, false); // TODO what is missing here? does this handle all cases?
    }

    _updatePosition(_entity, layerID, x, y, false);

    return true;





}

int map::toIndex(int const layer, const int x, const int y) {
    return   x + y*width + layer*width*Constants::NUM_LAYERS;
}

map::position map::toPosition(int const index) const {
    int x = index % width;
    int y = (index / width)%height;
    int z = index / (width*height);
    return map::position(x, y, z);
}

std::vector<tile*> map::getFreeSpawn(player* _player) {
    std::vector<tile*>freeSpawn;

    int spawnIdx = _player->_spawn[0];
    if(spawnIdx == 1) {
        // Goal is located in X plane
        int spawnX = _player->_spawn[spawnIdx];
        for(int spawnY = 0; spawnY < height; spawnY++){
            auto &tile = getTile(spawnX, spawnY);

            if(tile.isOccupied()){
                continue;
            }

            freeSpawn.push_back(&tile);
        }

    }else if(spawnIdx == 2){
        // goal is locaed in y plane
        int spawnY = _player->_spawn[spawnIdx];
        for(int spawnX = 0; spawnX < height; spawnX++){
            auto &tile = getTile(spawnX, spawnY);
            if(tile.isOccupied()){
                continue;
            }
            freeSpawn.push_back(&tile);
        }
    }else{
        throw std::runtime_error("Incorrect plane selected in freeSpawn");
    }



    return freeSpawn;
}

tile &map::getTile(int x, int y) {

    auto index = toIndex(0, x, y);
    auto &tile = tiles[index]; // Todo
    assert(tile.x == x && tile.y == y);

    return tile;
}

