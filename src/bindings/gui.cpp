#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../gui.h"
#include "../game.h"
namespace py = pybind11;

void init_gui(py::module &m) {
    py::class_<gui>(m, "GUI", py::dynamic_attr())
            .def(py::init<int, int, game&>())
            .def("event", &gui::event)
            .def("render", &gui::render);


}
