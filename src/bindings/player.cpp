#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../player.h"
#include "../game.h"

namespace py = pybind11;

void init_player(py::module &m) {
    py::class_<player>(m, "player")
            .def(py::init<game&>())
            .def(py::init<const player&>())
            .def_readonly("health", &player::health)
            .def_readonly("gold", &player::gold)
            .def_readonly("lumber", &player::lumber)
            .def_readonly("gold_income", &player::goldIncome)
            .def_readonly("terminal", &player::terminal)
            .def_readonly("state_layers", &player::_stateLayers, py::return_value_policy::reference)
            .def_readonly("movement", &player::_movement, py::return_value_policy::reference)
            .def_readonly("opponents", &player::_opponents, py::return_value_policy::reference)
            .def_readonly("entities", &player::_entities, py::return_value_policy::reference)
            .def_readonly("goal", &player::_goal, py::return_value_policy::reference)
            .def_readonly("spawn", &player::_spawn, py::return_value_policy::reference)
            .def("update", &player::update)
            .def("add_entity", &player::addEntity)
            .def("setup", &player::setup)
            .def("setup_opponents", &player::setupOpponents)
            .def("update_income", &player::updateIncome)
            .def("afflict_damage", &player::afflictDamage)
            .def("reset", &player::reset)
            .def("trigger_income", &player::triggerIncome)
            .def("calculateSpawn", &player::calculateSpawn)
            .def("calculateGoal", &player::calculateGoal);
            //.def_readonly("game", player::_game)


}