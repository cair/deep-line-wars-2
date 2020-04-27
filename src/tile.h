//
// Created by per on 19.04.2020.
//

#ifndef DEEPLINEWARS_TILE_H
#define DEEPLINEWARS_TILE_H
#include <map>
class entity;
class map;
class tile {

public:
    int x;
    int y;
    map &_map;

    std::map<int, entity*> _entities;

    tile(map & _map, int x, int y);
    //tile(const tile& obj);

    bool isOccupied();

    void reset();
};


#endif //DEEPLINEWARS_TILE_H
