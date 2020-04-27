//
// Created by per on 20.04.2020.
//

#include <iostream>
#include "gui.h"
#include "game.h"
#include "player.h"
#include "gui_entity.h"
#include "gui_player.h"

gui::gui(int width, int height, game& _game):
        _game(_game),
        enabled(_game._c.gui),
        width(width),
        height(height),
        tileRatioWidth(_game._c.windowWidth / width),
        tileRatioHeight(_game._c.windowHeight / height),
        guiPlayers(),
        window(sf::VideoMode(_game._c.windowWidth, _game._c.windowHeight), "Deep Line Wars v2.0"),
        gridLines(sf::Lines)
{
    if(!enabled){
        return;
    }

    for(auto &_player: _game._players){
        guiPlayers.emplace_back(*this, &_player);
    }

    for(auto &gui_player: guiPlayers){
        gui_player.setup();
        playerMapping[gui_player._player->id] = &gui_player;
    }

    setup();
}


void gui::setup(){
    setupGrid();
    setupEmitters();


}


void gui::setupEmitters(){
    _game._emitter.on(Constants::EmitterState::MOUSE_MOVE, [this](int playerID){
        playerMapping[playerID]->updateCursor();
    });

    _game._emitter.on(Constants::EmitterState::GAME_RESET, [this]{
        this->reset();
    });

    _game._emitter.on(Constants::EmitterState::PLAYER_INIT, [this](int playerID){
        playerMapping[playerID]->updateColor();
    });

    _game._emitter.on(Constants::EmitterState::PLAYER_HEALTH_CHANGE, [this](int playerID){
        playerMapping[playerID]->updateColor();
    });

    _game._emitter.on(Constants::EmitterState::UNIT_MOVE, [this](entity &_entity){
        this->updateUnitPosition(_entity);
    });

    _game._emitter.on(Constants::EmitterState::UNIT_DELETE, [this](entity &_entity){
        this->deleteUnit(_entity);
    });

    auto cbAdd = [this](entity &_entity){
        this->addUnit(_entity);
        this->updateUnitPosition(_entity);
    };
    _game._emitter.on(Constants::EmitterState::UNIT_ADD, cbAdd);
    _game._emitter.on(Constants::EmitterState::BUILDING_ADD, cbAdd);
}

void gui::reset(){
    for(auto &gui_player: guiPlayers){
        gui_player.reset();
    }
}

void gui::setupGrid(){
    // Setup grid along horizontal
    for(int y = 0; y < height; y++) {
        gridLines.append(sf::Vector2f(0, y * tileRatioHeight));
        gridLines.append(sf::Vector2f(_game._c.windowWidth, y * tileRatioHeight));
    }

    for(int x = 0; x < width; x++) {
        gridLines.append(sf::Vector2f(x * tileRatioWidth, 0));
        gridLines.append(sf::Vector2f(x * tileRatioWidth, _game._c.windowWidth));
    }

}

void gui::updateUnitPosition(entity &_entity){
    playerMapping[_entity._player->id]->sprites.at(_entity.id).updatePosition();
}

void gui::deleteUnit(entity &_entity){
    playerMapping[_entity._player->id]->sprites.erase(_entity.id);
}

void gui::addUnit(entity &_entity){
    auto &guiPlayer = playerMapping[_entity._player->id];

    guiPlayer->sprites.try_emplace(_entity.id, *guiPlayer, _entity);
    //sprites[_entity.id].
}


void gui::event(){
    if(!enabled){
        return;
    }
    // Process events
    sf::Event event;
    while (window.pollEvent(event))
    {
        // Close window: exit
        if (event.type == sf::Event::Closed){
            window.close();
            std::exit(0);
        }

    }
}

void gui::render(){
    if(!enabled){
        return;
    }
    // Clear screen
    window.clear();


    for(auto &gui_player: guiPlayers){
        window.draw(gui_player.territory);
    }
    for(auto &gui_player: guiPlayers){
        for(auto &entity: gui_player.sprites){
            entity.second.render(window);
        }
        window.draw(gui_player.mouseCursor);
    }

    window.draw(gridLines);

    // Draw the sprite
    //window.draw(sprite);
    // Draw the string
    //window.draw(text);
    // Update the window
    window.display();

}