//
// Created by per on 17.04.2020.
//

#ifndef DEEPLINEWARS_SHOP_H
#define DEEPLINEWARS_SHOP_H
#include <cpptoml.h>

class game;
class player;
class entity;

class shop {
private:
    int const err = -5000;
    game &_game;
    std::shared_ptr<cpptoml::table> _data;
    bool configLoaded();
    void loadEntities();

    std::map<int, entity> _entities;
public:
    explicit shop(game& game);

    static bool canAfford(player& player, entity &entity);

    bool purchase(player& player, int unitID);

    bool purchase(player &player, int unitID, int x, int y);

    bool canPlace(player &_player, int x, int y);

    entity& _addEntity(player &_player, entity &_entity);
};


#endif //DEEPLINEWARS_SHOP_H
