#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../game.h"
#include "../map.h"

namespace py = pybind11;

void init_map(py::module &m) {
    py::class_<map>(m, "Map")
        .def(py::init<game&, int, int>())
        .def("setup", &map::setup)
        .def("to_index", &map::toIndex)
        .def("to_position", &map::toPosition)
        .def("get_tile", &map::getTile, py::return_value_policy::reference)
        .def("update_position", &map::updatePosition)
        .def("get_free_spawn", &map::getFreeSpawn, py::return_value_policy::reference)
        .def_readonly("width", &map::width)
        .def_readonly("height", &map::height)
        .def_readonly("state", &map::state)
        .def_readonly("tiles", &map::tiles, py::return_value_policy::reference);
    //  // TODO - hide _ version




}
