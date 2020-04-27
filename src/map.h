//
// Created by per on 17.04.2020.
//

#ifndef DEEPLINEWARS_MAP_H
#define DEEPLINEWARS_MAP_H

#include <vector>
#include <array>
#include <memory>
#include "tile.h"
// https://stackoverflow.com/questions/16065183/convert-a-stdvector-to-a-numpy-array-without-copying-data
class game;
class entity;
class player;

class map {

public:
    game& _game;
    struct position {
        int x;
        int y;
        int z;
        position(int x, int y, int z): x(x), y(y), z(z){}
    };

    map(game& _game, int width, int height);

    void setup();
    int toIndex(int layer, int x, int y);
    [[nodiscard]] position toPosition(int index) const;
    tile& getTile(int x, int y);
    bool _updatePosition(entity &_entity, int layer, int x, int y, bool sum=false);
    bool updatePosition(entity &_entity, int x, int y);

    int const width;
    int const height;
    std::vector<int> state;
    std::vector<tile> tiles;
    std::vector<tile*> getFreeSpawn(player* _player);


    void reset();

    void removeUnit(entity &entity);
};


#endif //DEEPLINEWARS_MAP_H
