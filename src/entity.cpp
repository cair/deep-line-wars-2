#include <stdexcept>
#include <iostream>
#include <cmath>
#include "entity.h"
#include "game.h"
#include "player.h"
#include <experimental/random>

static int counter = 1;
entity::entity(game& _game):
id(counter++),
_game(&_game),
_attack(this)
{
    //std::cout << "Entity - Should be called ONCE" << std::endl;
    reset();
}

entity::entity(const entity &obj):
id(counter++),
_game(obj._game),
spawned(false),
_attack(obj._attack),
entityID(obj.entityID),
category(obj.category),
health(obj.health),
speed(obj.speed),
armor(obj.armor),
level(obj.level),
cost_gold(obj.cost_gold),
drop_gold(obj.drop_gold),
tickMoveCounter(0),
tickSpeed((speed == 0) ? 0.0 : speed / _game->_c.ticksPerSecond),
x(-5000),
y(-5000)
{
    _attack._entity = this;
    reset();
    //std::cout << "Entity - Should be called" << std::endl;
}

entity::entity():
_game(nullptr),
_attack(this)
{
    //std::cout << "Should not be called" << std::endl;
    throw std::runtime_error("Cannot continue with this inefficiency!");
}

void entity::reset(){
    tickMoveCounter = 0;
}


void entity::spawn(){

    for(int i = level; i < _player->level; i++){
        upgrade(i);
    }
    level = _player->level;

    auto spawnTiles = std::move(_game->_map.getFreeSpawn(_player)); // TODO move?
    if(spawnTiles.empty()){
        return;
    }

    // std::sample(
    // spawnTiles.begin(),
    // spawnTiles.end(),
    // std::back_inserter(out),
    // 1,
    // std::mt19937{std::random_device{}()
    // }); // TODO slow?
    int randomTileIdx = std::experimental::randint(0, static_cast<int>(spawnTiles.size() - 1));
    auto tile = spawnTiles[randomTileIdx];

    x = tile->x;
    y = tile->y;
    tile->_entities.try_emplace(id, this);
    spawned = true;
    _game->_emitter.emit(Constants::EmitterState::UNIT_ADD, *this);
}

bool entity::update() {

    if(health <= 0){
        return true;
    }

    if(!spawned){
        spawn();
        return false;
    }

    if(speed > 0){
        move();

        if(isGoal()){
            for(auto &opponent: _player->_opponents) {
                opponent->afflictDamage(1);
            }

            return true;
        }
    }

    if(_attack.enabled) {
        _attack.update();
    }

    return false;

}

void entity::despawn(){
    _game->_emitter.emit(Constants::EmitterState::UNIT_DELETE, *this);
    _game->_map.removeUnit(*this);
}


void entity::move(){

    tickMoveCounter += tickSpeed;
    if(tickMoveCounter < _game->_c.mechanics.tickEntityMove){
        if(_game->_c.mechanics.renderEveryStep){
            _game->_emitter.emit(Constants::EmitterState::UNIT_MOVE, *this);
        }
        return;
    }

    tickMoveCounter = 0;

    int newX = x + _player->_movement.first;
    int newY = y + _player->_movement.second;
    //std::cout << "x=" << x << ",y=" << y << std::endl;
    _game->_map.updatePosition(*this, newX, newY);
    _game->_emitter.emit(Constants::EmitterState::UNIT_MOVE, *this);

}

bool entity::isGoal(){
    int goalIdx = _player->_goal[0];
    if(goalIdx == 1){
        return x == _player->_goal[goalIdx];
    } else if(goalIdx == 2){
        return y == _player->_goal[goalIdx];
    }else {
        throw std::runtime_error("Invalid goalIdx. Should be 1 or 2 where 1 refers to the 1st index in goal array");
    }

}


entity& entity::setup(int _entityID, int _id, int _health, float _speed, int _armor, int _level, int _cost_gold, int _drop_gold, int _category) {
    entityID = _entityID;
    id = _id;
    health = _health;
    speed = _speed;
    armor = _armor;
    level = _level;
    cost_gold = _cost_gold;
    drop_gold = _drop_gold;
    category = _category;

    // Upgrade to correct level
    return *this;
}

void entity::verify() {
    if(
            id == err ||
            health == err ||
            speed == err ||
            armor == err ||
            level == err ||
            cost_gold == err ||
            drop_gold == err
            ){
        throw std::runtime_error("error");
    }
}

void entity::setPlayer(player *p) {
    _player = p;
}

void entity::afflictDamage(int amount) {
    health -= amount;
}

void entity::directSpawn(int _x, int _y) {
    x = _x;
    y = _y;
    spawned = true;
    _game->_map.getTile(x, y)._entities.try_emplace(id, this);
    _game->_emitter.emit(Constants::EmitterState::BUILDING_ADD, *this);
}

void entity::upgrade(int _level){
    auto multiplier = std::pow(1.0 + _game->_c.mechanics.upgradeEffectFactor, _level);

    health *= multiplier;
}
