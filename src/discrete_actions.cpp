//
// Created by per on 23.04.2020.
//
#include "spdlog/spdlog.h"
#include "discrete_actions.h"
#include <experimental/random>

int discrete_actions::sample() {
    return std::experimental::randint(0, (int)space.size()-1);
}

bool discrete_actions::sampleAction() {
    auto i = sample();
    //spdlog::debug("Sampled action: {0:d}", i);
    return space[i]();
}

discrete_actions::discrete_actions(game &g) : actions(g),
space({
              [this](){
                  //spdlog::debug("Purchase Militia");
                  return this->buyMilitia();
                  },
              [this](){
                  //spdlog::debug("Purchase Footman");
                  return this->buyFootman();
                  },
              [this](){
                  //spdlog::debug("Purchase Grunt");
                  return this->buyGrunt();
              },
              [this](){
                  //spdlog::debug("Purchase ArmoredGrunt");
                  return this->buyArmoredGrunt();
              },
              [this](){
                  //spdlog::debug("Purchase BasicTower");
                  return this->buyBasicTower();
              },
              [this](){
                  //spdlog::debug("Purchase FastTower");
                  return this->buyFastTower();
              },
              [this](){
                  //spdlog::debug("Purchase FasterTower");
                  return this->buyFasterTower();
              },
              [this](){
                  //spdlog::debug("Mouse move left");
                  return this->mouseMoveLeft();
              },
              [this](){
                  //spdlog::debug("Mouse move right");
                  return this->mouseMoveRight();
              },
              [this](){
                  //spdlog::debug("Mouse move up");
                  return this->mouseMoveUp();
              },
              [this](){
                  //spdlog::debug("Mouse move down");
                  return this->mouseMoveDown();
              },
              [this](){
                  //spdlog::debug("Mouse move down");
                  return this->upgrade();
              }
      }){

}
