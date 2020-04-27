cmake_minimum_required(VERSION 3.10.2)
project(DeepLineWars)

# Set Variables
set(ZMQ_BUILD_TESTS "")
set(CMAKE_CXX_STANDARD 17)
set(PYBIND11_CPP_STANDARD -std=c++17) # Experimental C++17 support
set(JSON_BuildTests OFF CACHE INTERNAL "")


include_directories(include/spdlog/include)
include_directories(include/seasocks/src/main/c)
include_directories(include/json/include)
if (NOT DEFINED PYTHON_BUILD)
        add_subdirectory(include/SFML EXCLUDE_FROM_ALL)
else()
        include_directories(include/SFML/include)
endif()

add_subdirectory(include/libzmq EXCLUDE_FROM_ALL)
add_subdirectory(include/cppzmq EXCLUDE_FROM_ALL)
add_subdirectory(include/pybind11 EXCLUDE_FROM_ALL)
include_directories(include/cpptoml/include)
include("include/cmrc/CMakeRC.cmake")


cmrc_add_resource_library(dlw ALIAS dlw::rc
        resources/entities.toml
        resources/sprites/units/militia.png
        resources/sprites/units/grunt.png
        resources/sprites/units/footman.png
        resources/sprites/units/armored_grunt.png
        resources/sprites/buildings/archer_den.png
        resources/sprites/buildings/tower_1.png
        resources/sprites/buildings/tower_2.png
        resources/sprites/buildings/lazer_tower.png
        resources/sprites/buildings/sun_altar.png
        resources/sprites/buildings/spike_machine.png
        resources/sprites/buildings/slow_tower.png
        resources/sprites/buildings/rootslinger.png
        )
set_property(TARGET dlw PROPERTY POSITION_INDEPENDENT_CODE ON)


set(SOURCE_FILES
        runner.cpp
        actions.cpp
        actions.h
        constants.h
        game.cpp
        game.h
        player.cpp
        player.h
        map.cpp
        map.h
        entity.cpp
        entity.h
        shop.cpp
        shop.h
        attack.cpp
        attack.h
        config/config.h
        config/mechanic.h
        tile.cpp
        tile.h
        gui.cpp
        gui.h
        gui_player.cpp
        gui_player.h
        gui_entity.cpp
        gui_entity.h
        emitter.cpp
        emitter.h
        virtual_mouse.cpp
        virtual_mouse.h
        discrete_actions.cpp
        discrete_actions.h

        server.h
        )


set(COMMON_LINK_LIBRARIES dlw::rc sfml-graphics sfml-window sfml-system libzmq cppzmq)

if (DEFINED PYTHON_BUILD)
        pybind11_add_module(Engine
                ${SOURCE_FILES}
                bindings/deeplinewars.cpp
                bindings/discrete_actions.cpp
                #bindings/gui.cpp
                bindings/game.cpp
                bindings/config.cpp
                bindings/actions.cpp
                bindings/attack.cpp
                bindings/entity.cpp
                bindings/map.cpp
                bindings/player.cpp
                bindings/shop.cpp
                bindings/tile.cpp
                bindings/mechanic.cpp
                bindings/constants.cpp
                )
        target_link_libraries(Engine PRIVATE ${COMMON_LINK_LIBRARIES})
else()
        add_executable(DeepLineWarsGame ${SOURCE_FILES})
        target_link_libraries(DeepLineWarsGame PRIVATE
        pybind11::embed
        ${COMMON_LINK_LIBRARIES}
        )
endif()


