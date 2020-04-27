//
// Created by per on 19.04.2020.
//

#include "tile.h"
#include "map.h"
#include "entity.h"

tile::tile(map &_map, int x, int y):
_map(_map),
_entities(),
x(x),
y(y)
{

    //std::cout << "Tile -- x:" << x << ",y:" << y << std::endl;

}

bool tile::isOccupied() {
    auto occupied = !_entities.empty();

    return !_entities.empty();
}

void tile::reset(){
    _entities.clear();
}