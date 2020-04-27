#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../shop.h"
#include "../game.h"
#include "../player.h"

namespace py = pybind11;

void init_shop(py::module &m) {
    py::class_<shop>(m, "shop", py::dynamic_attr())
            .def(py::init<game&>())
            .def("can_afford", &shop::canAfford)
            .def("can_place", &shop::canPlace)
            .def("purchase", (bool (shop::*)(player&, int)) &shop::purchase)
            .def("purchase", (bool (shop::*)(player&, int, int, int))&shop::purchase)
        ;

    // TODO - Missing privatre fields
}
