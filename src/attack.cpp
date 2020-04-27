//
// Created by per on 18.04.2020.
//

#include "attack.h"
#include <cmath>
#include <iostream>
#include "player.h"
#include "experimental/random"
#include "entity.h"


/*
attack::attack(entity& _e, int min, int max, int pen, int speed, int range):
min(min),
max(max),
pen(pen),
speed(speed),
range(range)
{

}*/



void attack::update() {
    // TODO this should perhaps be improved?
    // Grid search of some kind?
    for(auto opponent: _entity->_player->_opponents){


        for(auto &entity: opponent->_entities){
            //std::cout << "opponent entities" << std::endl;
            if(!inRange(entity)){
                continue;
            }

            int damage = sample(entity);
            entity.afflictDamage(damage);

        }

    }

}

attack::attack(entity *_e):
_entity(_e)
{
}


/*
attack::attack(const attack &obj):
_entity(obj._entity),
min(obj.min),
max(obj.max),
pen(obj.pen),
speed(obj.speed),
range(obj.range),
enabled(obj.enabled),
err(obj.err){
//std::cout << "copy lollll" << obj.enabled <<  std::endl;
}*/


bool attack::inRange(entity &opEntity){
    return hypot(_entity->x - opEntity.x, _entity->y - opEntity.y) <= range;
}

void attack::setup(int _min, int _max, int _pen, int _speed, int _range) {
    min = _min;
    max = _max;
    pen = _pen;
    speed = _speed;
    range = _range;

}

int attack::sample(entity &_opEntity) {

    return std::experimental::randint(min, max) - std::min(0, _opEntity.armor - pen);
}


