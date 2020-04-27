//
// Created by per on 17.04.2020.
//

#ifndef SRC_GAME_H
#define SRC_GAME_H

#include <chrono>
#include <vector>
#include "player.h"
#include "shop.h"
#include "map.h"
#include "config/config.h"
#include <cmrc/cmrc.hpp>
#include "actions.h"
#include "gui.h"
#include "emitter.h"

CMRC_DECLARE(dlw);

class game {

public:

    long gameCount = 0;
    long tickSum = 0;
    int const width;
    int const height;
    bool terminal = false;
    const config _c;
    cmrc::embedded_filesystem fs;
    map _map;
    emitter _emitter;
    std::vector<player> _players;
    gui _gui;
    std::chrono::high_resolution_clock::time_point startTime;

    player *selectedPlayer = nullptr;
    player *winner = nullptr;
    actions action;
    long tick = 0;


    game(int width, int height);
    game(int width, int height, config c);

    ~game();

    player &getPlayer(int idx);
    void selectPlayer(int idx);
    void update();
    void event();
    void render();


    shop _shop;


    void setup();

    void reset();

    long averageTick();
};


#endif //SRC_GAME_H
