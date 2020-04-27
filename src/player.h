//
// Created by per on 17.04.2020.
//

#ifndef DEEPLINEWARS_PLAYER_H
#define DEEPLINEWARS_PLAYER_H

#include <vector>
#include <list>
#include <map>
#include "constants.h"
#include "entity.h"
#include "virtual_mouse.h"

class game;

class player {
    int const err = -5000;

public:

    player(const player &_player);
    explicit player(game& _game);

    int const id;
    int level = 0;
    int health = err;
    unsigned long gold = err;
    unsigned long lumber = err;
    unsigned long goldIncome = err;
    bool terminal = false;
    game & _game;

    std::map<int, Constants::StateLayersPlayers> _stateLayers;
    std::pair<int, int> const _movement;

    std::array<int, 3> _goal;
    std::array<int, 3> calculateGoal();

    std::array<int, 3> _spawn;
    std::array<int, 3> calculateSpawn();

    std::array<float, 4> _territory;
    std::array<float, 4> calculateTerritory() const;

    std::vector<player*> _opponents;
    std::list<entity> _entities;

    virtual_mouse mouse;

    void update();
    entity& addEntity(entity & entity);
    void setup();
    void setupOpponents();
    void updateIncome(unsigned long &income, int cost) const;

    void afflictDamage(int amount);
    void reset();

    void triggerIncome();


    bool inTerritory(int x, int y);

    bool upgrade();
};


#endif //DEEPLINEWARS_PLAYER_H
