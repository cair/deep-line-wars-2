//
// Created by per on 23.04.2020.
//

#ifndef DEEPLINEWARS_VIRTUAL_MOUSE_H
#define DEEPLINEWARS_VIRTUAL_MOUSE_H
class player;

class virtual_mouse {

public:
    int maxX{};
    int maxY{};
    int x{};
    int y{};
    player &_player;

    explicit virtual_mouse(player &_player);
    virtual_mouse(player &_player, bool);

    void setPosition(double x, double y);
    void setPosition(int x, int y);
    bool moveLeft();
    bool moveRight();
    bool moveUp();
    bool moveDown();
};


#endif //DEEPLINEWARS_VIRTUAL_MOUSE_H
