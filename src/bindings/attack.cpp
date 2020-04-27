
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../attack.h"
#include "../entity.h"
namespace py = pybind11;

void init_attack(py::module &m) {
    py::class_<attack>(m, "Attack")
            .def(py::init<entity*>())
            //.def_readwrite("entity", &attack::_entity)
            .def_readonly("min", &attack::min)
            .def_readonly("max", &attack::max)
            .def_readonly("pen", &attack::pen)
            .def_readonly("speed", &attack::speed)
            .def_readonly("range", &attack::range)
            .def_readonly("enabled", &attack::enabled)


            .def("update", &attack::update)
            .def("sample", &attack::sample)
            .def("setup", &attack::setup)
            .def("inRange", &attack::inRange);



}
