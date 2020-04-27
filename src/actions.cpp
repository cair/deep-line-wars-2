//
// Created by per on 20.04.2020.
//

#include "actions.h"
#include "game.h"
#include <iostream>



actions::actions(game &_g):
g(_g)
{}

bool actions::buyMilitia() {
    return buy(Constants::Entity::MILITIA);
}

bool actions::buyFootman() {
    return buy(Constants::Entity::FOOTMAN);
}

bool actions::buyGrunt() {
    return buy(Constants::Entity::GRUNT);
}

bool actions::buyArmoredGrunt() {
    return buy(Constants::Entity::ARMORED_GRUNT);
}

bool actions::buyBasicTower() {
    return buyBuilding(Constants::Entity::BASIC_TOWER);
}

bool actions::buyFastTower() {
    return buyBuilding(Constants::Entity::FAST_TOWER);
}

bool actions::buyFasterTower() {
    return buyBuilding(Constants::Entity::FASTER_TOWER);
}

bool actions::mouseMoveLeft() {
    return g.selectedPlayer->mouse.moveLeft();
}

bool actions::mouseMoveRight() {
    return g.selectedPlayer->mouse.moveRight();
}

bool actions::mouseMoveUp() {
    return g.selectedPlayer->mouse.moveUp();
}

bool actions::mouseMoveDown() {
    return g.selectedPlayer->mouse.moveDown();
}

bool actions::upgrade() {
    return g.selectedPlayer->upgrade();
}


/*
bool actions::mouseMoveContinuousX(double x) {
    return false;
}

bool actions::mouseMoveContinuousY(double x) {
    return false;
}

bool actions::mouseMoveAbsoluteX(int x) {
    return false;
}

bool actions::mouseMoveAbsoluteY(int x) {
    return false;
}

bool actions::mouseMoveContinuous(double x, double y) {
    return false;
}

bool actions::mouseMoveAbsolute(int x, int y) {
    return false;
}

 */

bool actions::buy(Constants::Entity e) {
    return g._shop.purchase(*g.selectedPlayer, e);
}

bool actions::buyBuilding(Constants::Entity e) {
    return g._shop.purchase(*g.selectedPlayer, e, g.selectedPlayer->mouse.x, g.selectedPlayer->mouse.y);
}
