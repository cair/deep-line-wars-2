#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../config/mechanic.h"

namespace py = pybind11;

void init_mechanic(py::module &m) {
    py::class_<mechanic>(m, "mechanic")
            .def(py::init<>())
            .def_readwrite("tickEntityMove", &mechanic::tickEntityMove);
}