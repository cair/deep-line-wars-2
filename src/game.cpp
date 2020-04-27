//
// Created by per on 17.04.2020.
//
#include <iostream>
#include "game.h"
#include "emitter.h"

game::game(int const width, int const height):
game(width, height, config())
{}



game::game(int const width, int const height, config c):
_c(c),
width(width),
height(height),
fs(cmrc::dlw::get_filesystem()),
_map(*this, width, height),
_shop(*this),
_players(2, player(*this)),
_gui(width, height, *this),
action(*this)
{
    setup();
}

void game::setup(){
    for(auto &p: _players){
        p.setup();
    }
    selectPlayer(0);
    startTime = std::chrono::high_resolution_clock::now();
}

void game::reset(){
    for(auto &p: _players){
        p.reset();
    }
    _map.reset();
    terminal = false;
    winner = nullptr;
    gameCount += 1;
    tickSum += tick;
    tick = 0;
    _emitter.emit(Constants::EmitterState::GAME_RESET);
}

long game::averageTick(){
    return tickSum / gameCount;
}

void game::update() {
    if(terminal){
        return;
    }
    tick++;
    bool incomeTick = tick % _c.incomeFrequency == 0;

    int aliveCount = 0;

    //std::cout << "STARTING HERE" << std::endl;

    for(auto &player: _players){
        if(incomeTick){
            player.triggerIncome();
        }
        //std::cout << "INCOME_DONE" << std::endl;
        player.update();
        //std::cout << "UPDATE_DONE" << std::endl;
        if(!player.terminal){
            aliveCount++;
            winner = &player;
        }
        //std::cout << "TERMINAL_DONE" << std::endl;
    }

    if(aliveCount == 1){
        terminal = true;
    }else if(aliveCount == 0){
        // Draw
        winner = nullptr;
        terminal = true;
    }



}

player &game::getPlayer(int idx) {
    return _players[idx];
}

void game::selectPlayer(int idx) {
    if(0 > idx > _players.size()){
        throw std::runtime_error("Invalid selectPLayer action. Must be in abouts (0-4(2))");
    }

    selectedPlayer = &_players[idx];
}

void game::event() {
    _gui.event();
}

void game::render() {
    _gui.render();
}

game::~game()= default;
