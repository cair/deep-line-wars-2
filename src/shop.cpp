//
// Created by per on 17.04.2020.
//

#include <iostream>
#include "shop.h"
#include "game.h"
#include "attack.h"
#include "constants.h"
#include "entity.h"


shop::shop(game& _g):
_game(_g),
_data(cpptoml::parse_string(_game.fs.open("resources/entities.toml").begin()))
{
    loadEntities();
}




bool shop::configLoaded() {
   return false;
}

void shop::loadEntities() {
    for(const auto& eData: *_data->as_table()){
        auto values = eData.second->as_table();
        auto attackValues = values->get_table("attack");

        std::shared_ptr<cpptoml::table> avTable = nullptr;
        if(attackValues != nullptr){
            avTable = attackValues->as_table();
        }

        int unitID = Constants::UNIT_TO_UNIT_ID.at(eData.first);

        auto &entity = _entities.try_emplace(unitID, _game)
        .first->second.setup(
                unitID,
                values->get_as<int>("id").value_or(err),
                values->get_as<int>("health").value_or(err),
                values->get_as<double>("speed").value_or(err),
                values->get_as<int>("armor").value_or(err),
                values->get_as<int>("level").value_or(err),
                values->get_as<int>("cost_gold").value_or(err),
                values->get_as<int>("drop_gold").value_or(err),
                values->get_as<int>("category").value_or(err)
                );

        if(avTable){
            entity._attack.setup(
                    avTable->get_as<int>("min").value_or(err),
                    avTable->get_as<int>("max").value_or(err),
                    avTable->get_as<int>("pen").value_or(err),
                    avTable->get_as<int>("speed").value_or(err),
                    avTable->get_as<int>("range").value_or(err)
                    );
            entity._attack.enabled = true;
        }else{
            entity._attack.enabled = false;
        }




    }
}


entity& shop::_addEntity(player &_player, entity &_entity){
    _player.gold -= _entity.cost_gold;
    _player.updateIncome(_player.goldIncome, _entity.cost_gold);
    return _player.addEntity(_entity);
}


bool shop::canAfford(player &player, entity &entity) {
    return player.gold >= entity.cost_gold; // TODO ADD WOOD ETC
}

bool shop::canPlace(player &_player, int x, int y){
    auto &tile = _game._map.getTile(x, y);
    return !tile.isOccupied() && _player.inTerritory(x, y);
}

bool shop::purchase(player &player, const int unitID, const int x, const int y) {

    entity &_newEntity = _entities[unitID];

    if(!canAfford(player, _newEntity)){
        return false;
    }

    if(!canPlace(player, x, y)){
        return false;
    }

    auto &savedEntity = _addEntity(player, _newEntity);
    savedEntity.directSpawn(x, y);

    return true;
}

bool shop::purchase(player &_player, const int unitID) {

    entity &_entity = _entities[unitID];

    if(!canAfford(_player, _entity)){
        return false;
    }

    _addEntity(_player, _entity);

    return true;
}


