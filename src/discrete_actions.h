//
// Created by per on 23.04.2020.
//

#ifndef DEEPLINEWARS_DISCRETE_ACTIONS_H
#define DEEPLINEWARS_DISCRETE_ACTIONS_H
#include "actions.h"
#include <functional>

#include <map>
typedef std::function<bool()> sig;
class discrete_actions: actions {
    std::vector<sig> space;

public:
    explicit discrete_actions(game &g);

    int sample();
    bool sampleAction();


};


#endif //DEEPLINEWARS_DISCRETE_ACTIONS_H
