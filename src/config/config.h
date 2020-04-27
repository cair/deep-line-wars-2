//
// Created by per on 18.04.2020.
//

#ifndef DEEPLINEWARS_CONFIG_H
#define DEEPLINEWARS_CONFIG_H
#include "mechanic.h"
class config {

public:
    mechanic mechanics;
    int startHealth = 50;
    int startGold = 50;
    int startLumber = 50;
    int startIncomeGold = 50;
    int incomeFrequency = 10;
    float incomeRatio = 0.20;
    float killGoldRatio = 0.10;
    float enemyTerritoryDecay = 0.10;
    float friendlyTerritoryDecay = 0.0001;
    int ticksPerSecond = 10;
    int windowWidth = 600;
    int windowHeight = 600;
    bool gui = true;
    int fps = 0;
    int ups = 0;

    //std::string dashboardAddress = "ipc:///tmp/dlw.sock";
    std::string dashboardAddress = "tcp://localhost:5555";

    config():
    mechanics(mechanic())

    {}




};


#endif //DEEPLINEWARS_CONFIG_H
