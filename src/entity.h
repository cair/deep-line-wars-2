//
// Created by per on 17.04.2020.
//

#ifndef DEEPLINEWARS_ENTITY_H
#define DEEPLINEWARS_ENTITY_H
#include <memory>
#include "attack.h"

class game;
class player;

class entity {

private:
    std::shared_ptr<game> _game;


public:
    attack _attack;

    player *_player;
    entity();
    explicit entity(game &game);
    entity(const entity &obj);

    bool update();

    void move();
    void setPlayer(player *_player);

    void afflictDamage(int amount);
    void directSpawn(int x, int y);
    entity& setup(
            int entityID = 0,
            int id = 0,
            int health = 0,
            float speed = 0,
            int armor = 0,
            int level = 0,
            int cost_gold = 0,
            int drop_gold = 0,
            int category = 0);

    void verify();
    bool spawned = false;
    int err = -5000;
    int entityID = err;
    int category = err;
    int health = err;
    int id = err;
    double speed = err;
    int armor = err;
    int level = err;
    int cost_gold = err;
    int drop_gold = err;
    double tickSpeed = err;

    double tickMoveCounter;

    void reset();

    int x;
    int y;

    bool isGoal();

    void spawn();

    void despawn();

    void upgrade(int level);
};


#endif //DEEPLINEWARS_ENTITY_H
