#include <pybind11/pybind11.h>
namespace py = pybind11;

#include "../constants.h"

void init_constants(py::module &m) {

    auto constants = m.def_submodule("Constants");

    constants.attr("MAX_PLAYERS") = py::int_(Constants::MAX_PLAYERS);

    py::enum_<Constants::Entity>(constants, "Entity", py::arithmetic(), "Entity ID Constants")
            .value("BASIC_TOWER", Constants::Entity::BASIC_TOWER)
            .value("FAST_TOWER", Constants::Entity::FAST_TOWER)
            .value("FASTER_TOWER", Constants::Entity::FASTER_TOWER)
            .value("MILITIA", Constants::Entity::MILITIA)
            .value("FOOTMAN", Constants::Entity::FOOTMAN)
            .value("GRUNT", Constants::Entity::GRUNT)
            .value("ARMORED_GRUNT", Constants::Entity::ARMORED_GRUNT);

    py::enum_<Constants::EntityCategory>(constants, "EntityCategory", py::arithmetic(), "Entity Category")
            .value("BUILDING", Constants::EntityCategory::BUILDING)
            .value("UNIT", Constants::EntityCategory::BUILDING);

    py::enum_<Constants::PlayerID>(constants, "PlayerID", py::arithmetic(), "Player ID")
            .value("PLAYER_1", Constants::PlayerID::PLAYER_1)
            .value("PLAYER_2", Constants::PlayerID::PLAYER_2)
            .value("PLAYER_3", Constants::PlayerID::PLAYER_3)
            .value("PLAYER_4", Constants::PlayerID::PLAYER_4);

    py::enum_<Constants::StateLayersPlayers>(constants, "StateLayersPlayers", py::arithmetic(), "StateLayersPlayers")
            .value("TILE_TYPE", Constants::StateLayersPlayers::TILE_TYPE)
            .value("P_1_ID", Constants::StateLayersPlayers::P_1_ID)
            .value("P_1_UNIT", Constants::StateLayersPlayers::P_1_UNIT)
            .value("P_1_UNIT_COUNT", Constants::StateLayersPlayers::P_1_UNIT_COUNT)
            .value("P_1_BUILDING", Constants::StateLayersPlayers::P_1_BUILDING)
            .value("P_1_BUILDING_COUNT", Constants::StateLayersPlayers::P_1_BUILDING_COUNT)
            .value("P_2_ID", Constants::StateLayersPlayers::P_2_ID)
            .value("P_2_UNIT", Constants::StateLayersPlayers::P_2_UNIT)
            .value("P_2_UNIT_COUNT", Constants::StateLayersPlayers::P_2_UNIT_COUNT)
            .value("P_2_BUILDING", Constants::StateLayersPlayers::P_2_BUILDING)
            .value("P_2_BUILDING_COUNT", Constants::StateLayersPlayers::P_2_BUILDING_COUNT)
            .value("P_3_ID", Constants::StateLayersPlayers::P_3_ID)
            .value("P_3_UNIT", Constants::StateLayersPlayers::P_3_UNIT)
            .value("P_3_UNIT_COUNT", Constants::StateLayersPlayers::P_3_UNIT_COUNT)
            .value("P_3_BUILDING", Constants::StateLayersPlayers::P_3_BUILDING)
            .value("P_3_BUILDING_COUNT", Constants::StateLayersPlayers::P_3_BUILDING_COUNT)
            .value("P_4_ID", Constants::StateLayersPlayers::P_4_ID)
            .value("P_4_UNIT", Constants::StateLayersPlayers::P_4_UNIT)
            .value("P_4_UNIT_COUNT", Constants::StateLayersPlayers::P_4_UNIT_COUNT)
            .value("P_4_BUILDING", Constants::StateLayersPlayers::P_4_BUILDING)
            .value("P_4_BUILDING_COUNT", Constants::StateLayersPlayers::P_4_BUILDING_COUNT)
            .value("NUM_LAYERS", Constants::StateLayersPlayers::NUM_LAYERS);

    py::enum_<Constants::StateLayer>(constants, "StateLayer", py::arithmetic(), "StateLayer Constants")
            .value("UNIT_ID", Constants::StateLayer::UNIT_ID)
            .value("UNIT_COUNT", Constants::StateLayer::UNIT_COUNT)
            .value("BUILDING_ID", Constants::StateLayer::BUILDING_ID)
            .value("BUILDING_COUNT", Constants::StateLayer::BUILDING_COUNT)
            .value("PLAYER_ID", Constants::StateLayer::PLAYER_ID);

    py::enum_<Constants::EmitterState>(constants, "EmitterState", py::arithmetic(), "EmitterState Constants")
            .value("UNIT_DELETE", Constants::EmitterState::UNIT_DELETE)
            .value("UNIT_MOVE", Constants::EmitterState::UNIT_MOVE)
            .value("PLAYER_HEALTH_CHANGE", Constants::EmitterState::PLAYER_HEALTH_CHANGE)
            .value("UNIT_ADD", Constants::EmitterState::UNIT_ADD)
            .value("GAME_RESET", Constants::EmitterState::GAME_RESET)
            .value("PLAYER_INIT", Constants::EmitterState::PLAYER_INIT)
            .value("BUILDING_ADD", Constants::EmitterState::BUILDING_ADD)
            .value("BUILDING_DELETE", Constants::EmitterState::BUILDING_DELETE)
            .value("MOUSE_MOVE", Constants::EmitterState::MOUSE_MOVE);

    // TODO missing PLAYER_STATE_LAYERS PLAYER_MOVEMENT UNIT_TO_UNIT_ID
}
