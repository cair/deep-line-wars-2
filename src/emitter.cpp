//
// Created by per on 21.04.2020.
//

#include "emitter.h"

emitter::emitter():
voidCbMap(),
intCbMap()
{

};


void emitter::on(Constants::EmitterState key, emitter::entityCB cb) {
    entityCBMap.try_emplace(key);
    entityCBMap[key].emplace_back(cb);
}


void emitter::on(Constants::EmitterState key, voidCB cb) {
    voidCbMap.try_emplace(key);
    voidCbMap[key].emplace_back(cb);
}

void emitter::on(Constants::EmitterState key, emitter::intCB cb) {
    intCbMap.try_emplace(key);
    intCbMap[key].emplace_back(cb);
}

void emitter::emit(Constants::EmitterState key, int val) {
    if(intCbMap.count(key)){
        for(auto &fn: intCbMap[key]){
            fn(val);
        }
    }
}

void emitter::emit(Constants::EmitterState key){

    if(voidCbMap.count(key)){
        for(auto &fn: voidCbMap[key]){
            fn();
        }
    }
}

void emitter::emit(Constants::EmitterState key, entity &_entity) {
    if(entityCBMap.count(key)){
        for(auto &fn: entityCBMap[key]){
            fn(_entity);
        }
    }
}




