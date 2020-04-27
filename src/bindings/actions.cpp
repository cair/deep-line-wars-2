
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../attack.h"
#include "../game.h"
namespace py = pybind11;

void init_actions(py::module &m) {
    py::class_<actions>(m, "Actions")
            .def(py::init<game &>())
            .def("buy", &actions::buy)
            .def("buy_militia", &actions::buyMilitia)
            .def("buy_footman", &actions::buyFootman)
            .def("buy_grunt", &actions::buyGrunt)
            .def("buy_armored_grunt", &actions::buyArmoredGrunt)
            .def("buy_basic_tower", &actions::buyBasicTower)
            .def("buy_fast_tower", &actions::buyFastTower)
            .def("buy_faster_tower", &actions::buyFasterTower)
            .def("mouse_move_left", &actions::mouseMoveLeft)
            .def("mouse_move_right", &actions::mouseMoveRight)
            .def("mouse_move_up", &actions::mouseMoveUp)
            .def("mouse_move_down", &actions::mouseMoveDown)
            .def("buy_building", &actions::buyBuilding)
            .def("upgrade", &actions::upgrade)


    ;
    // TODO space and more
}
