
#include <thread>
#include "game.h"
#include "config/config.h"
#include "discrete_actions.h"
#include "spdlog/spdlog.h"
#include "server.h"
#include <experimental/random>
int main(){

    spdlog::set_level(spdlog::level::debug);
    config c = config();
    c.mechanics.tickEntityMove = 10;
    c.gui = false;


    game g = game(12, 12, c);
    //APIServer api(g, true, true, 8080); // std::experimental::randint(30000, 60000)
    discrete_actions action(g);

    auto &player = g.getPlayer(0);
    auto &player1 = g.getPlayer(1);

    int episode = 0;
    int xto = 0;
    while(true){
        g.reset();
        while(!g.terminal){

            if(xto++ % 60 == 0) {
                g.selectPlayer(0);
                action.sampleAction();

                g.selectPlayer(1);
                action.sampleAction();
            }

            g.update();
            g._gui.event();
            g._gui.render();


        }
        episode++;

    }




    //std::cout << "lol" << std::endl;
}
