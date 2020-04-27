#include <cmath>

#include "player.h"
#include "game.h"
#include "constants.h"

static int counter = 0;
player::player(game &_game):
mouse(*this, false),
_game(_game),
id(-5000){}




player::player(const player &_player):
_game(_player._game),
id(++counter),
_stateLayers(Constants::PLAYER_STATE_LAYERS.at(id)),
_movement(Constants::PLAYER_MOVEMENT.at(id)),
_spawn(calculateSpawn()),
_goal(calculateGoal()),
_territory(calculateTerritory()),
mouse(*this)
{
    //std::cout << "Player copy -- " << id << std::endl;
    reset();
}



void player::update() {


    // Iterate over all entities and update.
    // if update returns false. its a disposable
    for (auto i = _entities.begin(); i != _entities.end();) {

        //std::cout << "entity_lol" << std::endl;
        if ((*i).update()){
            //std::cout << "delete" << std::endl;
            i->despawn();
            i = _entities.erase(i);
        }else{
            ++i;
        }

    }

}

entity& player::addEntity(entity &entity) {
    auto &addedEntity = _entities.emplace_back(std::move(entity));
    addedEntity.setPlayer(this);
    return addedEntity;
}

void player::setupOpponents() {

    for(auto &p: _game._players) {
        if(&p == this) {
            continue;
        }

        _opponents.push_back(&p);
    }

}

void player::setup() {
    this->setupOpponents();
    _game._emitter.emit(Constants::PLAYER_INIT, id);
}

void player::reset() {
    for(auto &tile: _game._map.tiles){
        tile.reset();
    }
    _entities.clear(); // TODO health etc.
    health = _game._c.startHealth;
    gold = _game._c.startGold;
    lumber = _game._c.startLumber;
    goldIncome = _game._c.startIncomeGold;
    level = 0;
    terminal = false;
}

std::array<int, 3> player::calculateGoal() {
    if(_movement.first == 1 and _movement.second == 0) {
        return {1, _game._map.width - 1, err};
    } else if(_movement.first == -1 and _movement.second == 0) {
        return {1, 0, err};
    } else if(_movement.first == 0 and _movement.second == 1) {
        return {2, err, _game._map.height - 1};
    } else if(_movement.first == 0 and _movement.second == -1) {
        return {2, err, 0};
    } else {
        throw std::runtime_error("Illegal state when calculating goal!");
    }

}

std::array<int, 3> player::calculateSpawn() {
    if(_movement.first == 1 and _movement.second == 0) {
        return {1, 0, err};
    } else if(_movement.first == -1 and _movement.second == 0) {
        return {1, _game._map.width-1, err};
    } else if(_movement.first == 0 and _movement.second == 1) {
        return {2, err, 0};
    } else if(_movement.first == 0 and _movement.second == -1) {
        return {2, err, _game._map.height-1};
    } else {
        throw std::runtime_error("Illegal state when calculating spawn!");
    }

}

bool player::upgrade(){
    auto upgradeCost = _game._c.mechanics.upgradeCostStart * std::pow((1.0 + _game._c.mechanics.upgradeCostFactor), level);
    if(gold < upgradeCost){
        return false;
    }
    gold -= upgradeCost;

    level += 1;
    for(auto &entity: _entities){
        entity.upgrade(level);
    }

    return true;
}



void player::triggerIncome(){
    gold += goldIncome;
}

void player::updateIncome(unsigned long &income, int const cost) const {
    //income can be gold, lumber ...etc
    // cost is the entity cost
    income += ceil((cost * _game._c.incomeRatio));


}


bool player::inTerritory(int x, int y){
    auto r0 = _territory[0]+_territory[2];
    auto r1 = (_territory[1] + _territory[3]);

    bool c1 = x >= _territory[0] && x < r0;
    bool c2 = y > _territory[1] && y < r1;
    return c1 && c2;
}

void player::afflictDamage(int amount) {
    health -= amount;
    if(health <= 0){
        terminal = true;
        return;
    }
    _game._emitter.emit(Constants::PLAYER_HEALTH_CHANGE, id);
}

std::array<float, 4> player::calculateTerritory() const {
    // P0 -> X0:XMID
    // P1 -> XMID:WIDTH
    // P2 -> Y0:MID
    // P3 -> YMID:HEIGHT
    // x1, y1, x2, y2
    if(id == 1){
        // Player 1
        return {
            1, 0,
            static_cast<float>(_game.width / 2.0) - 1, static_cast<float>(_game.height)};
     }else if(id == 2){
        return {
            static_cast<float>(_game.width / 2.0), 0,
            static_cast<float>(_game.width / 2.0) - 1 , static_cast<float>(_game.height)};
    } else {
        throw std::runtime_error("Not implemented territory for players > 2");
    }

}


