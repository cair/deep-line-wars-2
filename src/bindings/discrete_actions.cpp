#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../discrete_actions.h"
#include "../game.h"
namespace py = pybind11;

void init_discrete_actions(py::module &m) {
    py::class_<discrete_actions>(m, "DiscreteActions")
            .def(py::init<game &>())
            .def("sample_action", &discrete_actions::sampleAction)
            .def("sample", &discrete_actions::sample)



            ;
    // TODO space and more
}
