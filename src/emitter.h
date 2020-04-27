//
// Created by per on 21.04.2020.
//

#ifndef DEEPLINEWARS_EMITTER_H
#define DEEPLINEWARS_EMITTER_H

#include "constants.h"
#include <functional>
#include <map>
class entity;

class emitter {
    typedef std::function<void()> voidCB;
    typedef std::vector<voidCB> voidCBVector;
    std::map<Constants::EmitterState, voidCBVector> voidCbMap;

    typedef std::function<void(int)> intCB;
    typedef std::vector<intCB> intCBVector;
    std::map<Constants::EmitterState, intCBVector> intCbMap;

    typedef std::function<void(entity&)> entityCB;
    typedef std::vector<entityCB> entityCBVector;
    std::map<Constants::EmitterState, entityCBVector> entityCBMap;

public:
    emitter();

    void emit(Constants::EmitterState);
    void emit(Constants::EmitterState, int val);
    void emit(Constants::EmitterState, entity &_entity);
    void on(Constants::EmitterState key, voidCB cb);
    void on(Constants::EmitterState key, intCB cb);
    void on(Constants::EmitterState key, entityCB cb);
};


#endif //DEEPLINEWARS_EMITTER_H
