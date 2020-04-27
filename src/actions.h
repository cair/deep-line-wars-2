//
// Created by per on 20.04.2020.
//

#ifndef DEEPLINEWARS_ACTIONS_H
#define DEEPLINEWARS_ACTIONS_H
#include <vector>
#include "constants.h"
class game;

class actions {
game &g;
public:

    explicit actions(game &_g);
    bool buy(Constants::Entity);
    bool buyMilitia();
    bool buyFootman();
    bool buyGrunt();
    bool buyArmoredGrunt();
    bool buyBasicTower();
    bool buyFastTower();
    bool buyFasterTower();
    bool mouseMoveLeft();
    bool mouseMoveRight();
    bool mouseMoveUp();
    bool mouseMoveDown();
    bool buyBuilding(Constants::Entity e);
    bool upgrade();
    /*
    bool mouseMoveContinuousX(double x);
    bool mouseMoveContinuousY(double x);
    bool mouseMoveAbsoluteX(int x);
    bool mouseMoveAbsoluteY(int x);
    bool mouseMoveContinuous(double x, double y);
    bool mouseMoveAbsolute(int x, int y);*/

};


#endif //DEEPLINEWARS_ACTIONS_H
