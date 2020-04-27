//
// Created by per on 17.04.2020.
//

#ifndef DEEPLINEWARS_CONSTANTS_H
#define DEEPLINEWARS_CONSTANTS_H

#include <map>



namespace Constants{
    int const MAX_PLAYERS = 2;

    enum Entity{
        BASIC_TOWER = 1,
        FAST_TOWER = 2,
        FASTER_TOWER = 3,
        MILITIA = 4,
        FOOTMAN = 5,
        GRUNT= 6,
        ARMORED_GRUNT = 7
    };

    enum EntityCategory{
        BUILDING = 0,
        UNIT = 1
    };

    enum PlayerID {
        PLAYER_1 = 1,
        PLAYER_2 = 2,
        PLAYER_3 = 3,
        PLAYER_4 = 4
    };

    enum StateLayersPlayers {
        TILE_TYPE = 0,

        P_1_ID = 1,
        P_1_UNIT = 2,
        P_1_UNIT_COUNT = 3,
        P_1_BUILDING = 4,
        P_1_BUILDING_COUNT = 5,

        P_2_ID = 6,
        P_2_UNIT = 7,
        P_2_UNIT_COUNT = 8,
        P_2_BUILDING = 9,
        P_2_BUILDING_COUNT = 10,

        P_3_ID = 11,
        P_3_UNIT = 12,
        P_3_UNIT_COUNT = 13,
        P_3_BUILDING = 14,
        P_3_BUILDING_COUNT = 15,

        P_4_ID = 16,
        P_4_UNIT = 17,
        P_4_UNIT_COUNT = 18,
        P_4_BUILDING = 29,
        P_4_BUILDING_COUNT = 20,

        NUM_LAYERS = 10 // TODO increase for additional players
    };

    enum StateLayer {
        UNIT_ID = 1,
        UNIT_COUNT = 2,
        BUILDING_ID = 3,
        BUILDING_COUNT = 4,
        PLAYER_ID = 5
    };

    enum EmitterState {
        UNIT_DELETE = 1,
        UNIT_MOVE = 2,
        PLAYER_HEALTH_CHANGE = 3,
        UNIT_ADD = 4,
        GAME_RESET = 5,
        PLAYER_INIT = 6,
        BUILDING_ADD = 7,
        BUILDING_DELETE = 8,
        MOUSE_MOVE = 9
    };


    const std::map<int, std::map<int, StateLayersPlayers>> PLAYER_STATE_LAYERS = {
            {PLAYER_1, {
                {PLAYER_ID, P_1_ID},
                {UNIT_ID, P_1_UNIT},
                {UNIT_COUNT, P_1_UNIT_COUNT},
                {BUILDING_ID, P_1_BUILDING},
                {BUILDING_COUNT, P_1_BUILDING_COUNT}
            }},
            {PLAYER_2, {
                {PLAYER_ID, P_2_ID},
                {UNIT_ID, P_2_UNIT},
                {UNIT_COUNT, P_2_UNIT_COUNT},
                {BUILDING_ID, P_2_BUILDING},
                {BUILDING_COUNT, P_2_BUILDING_COUNT}
            }},
            {PLAYER_3, {
                {PLAYER_ID, P_3_ID},
                {UNIT_ID, P_3_UNIT},
                {UNIT_COUNT, P_3_UNIT_COUNT},
                {BUILDING_ID, P_3_BUILDING},
                {BUILDING_COUNT, P_3_BUILDING_COUNT}
            }},
            {PLAYER_4, {
                {PLAYER_ID, P_4_ID},
                {UNIT_ID, P_4_UNIT},
                {UNIT_COUNT, P_4_UNIT_COUNT},
                {BUILDING_ID, P_4_BUILDING},
                {BUILDING_COUNT, P_4_BUILDING_COUNT}
            }}
    };


    const std::map<int, std::pair<int, int>> PLAYER_MOVEMENT = {
            {PLAYER_1, {1, 0}},
            {PLAYER_2, {-1, 0}},
            {PLAYER_3, {0, 1}},
            {PLAYER_4, {0, -1}}
    };


    const std::map<std::string, int> UNIT_TO_UNIT_ID = {
            {"BasicTower", BASIC_TOWER},
            {"FastTower", FAST_TOWER},
            {"FasterTower", FASTER_TOWER},
            {"Militia", MILITIA},
            {"Footman", FOOTMAN},
            {"Grunt", GRUNT},
            {"ArmoredGrunt", ARMORED_GRUNT},
    };

}


#endif //DEEPLINEWARS_CONSTANTS_H
