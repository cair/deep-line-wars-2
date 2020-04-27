//
// Created by per on 18.04.2020.
//

#ifndef DEEPLINEWARS_ATTACK_H
#define DEEPLINEWARS_ATTACK_H

#include <memory>

class entity;
class player;

class attack {
public:
    entity *_entity;
    int err = -5000;
    int min = err;
    int max = err;
    int pen = err;
    int speed = err;
    int range = err;
    bool enabled = false;

    explicit attack(entity *_e);
    void update();

    int sample(entity &_opEntity);
    void setup(int min, int max, int pen, int speed, int range);

    bool inRange(entity &opEntity);
};


#endif //DEEPLINEWARS_ATTACK_H
