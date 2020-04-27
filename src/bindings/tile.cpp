#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../tile.h"
#include "../map.h"

namespace py = pybind11;

void init_tile(py::module &m) {
    py::class_<tile>(m, "tile")
            .def(py::init<map&, int, int>())
            .def("is_occupied", &tile::isOccupied)
            .def_readonly("x", &tile::x)
            .def_readonly("y", &tile::y)
            //.def_readonly("map", &tile::_map)
            //.def_property("x", &tile::entities)
            ;

    // TODO - Missing privatre fields
}