
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../game.h"

namespace py = pybind11;

void init_game(py::module &m) {
    py::class_<game>(m, "Game", py::dynamic_attr())
            .def(py::init<int, int, config>())
            .def(py::init<int, int>())
            .def("get_player", &game::getPlayer, py::return_value_policy::reference)
            .def("update", &game::update)
            .def("select_player", &game::selectPlayer)
            //.def("event", &game::event)
            .def("render", &game::render)
            .def("reset",  &game::reset)

            // Properties
            .def_readwrite("terminal", &game::terminal)
            .def_readwrite("tick", &game::tick)
            .def_readonly("selected_player", &game::selectedPlayer)
            .def_readwrite("gameCount", &game::gameCount)
            .def_readwrite("tickSum", &game::tickSum)
            .def_readonly("width", &game::width)
            .def_readonly("height", &game::height)
            .def_readonly("player", &game::winner)


                    // Dynamic attr
            .def_readonly("map", &game::_map, py::return_value_policy::reference)
            .def_readonly("shop", &game::_shop, py::return_value_policy::reference)
            .def_readonly("config", &game::_c, py::return_value_policy::reference)

            ;


}
