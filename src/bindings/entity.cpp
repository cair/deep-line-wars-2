#include <pybind11/pybind11.h>

namespace py = pybind11;

#include "../entity.h"
#include "../game.h"

namespace py = pybind11;

void init_entity(py::module &m) {
    py::class_<entity>(m, "Entity")
            .def(py::init<>()) // default
            .def(py::init<const entity&>()) // Copy constructor
            .def(py::init<game&>()) // Constructor

            .def_readonly("attack", &entity::_attack)
            .def_readonly("player", &entity::_player)
            .def("update", &entity::update)
            .def("set_player", &entity::setPlayer)
            .def("afflict_damage", &entity::afflictDamage)
            .def("setup", &entity::setup)
            .def("verify", &entity::verify)
            .def_readonly("spawned", &entity::spawned)
            .def_readonly("category", &entity::category)
            .def_readonly("health", &entity::health)
            .def_readonly("id", &entity::id)
            .def_readonly("speed", &entity::speed)
            .def_readonly("armor", &entity::armor)
            .def_readonly("level", &entity::level)
            .def_readonly("cost_gold", &entity::cost_gold)
            .def_readonly("drop_gold", &entity::drop_gold)
            .def_readonly("tickMoveCounter", &entity::tickMoveCounter)
            .def_readonly("x", &entity::y)
            .def_readonly("y", &entity::x)
            .def("isGoal", &entity::isGoal)
            .def("spawn", &entity::spawn)


            ;

}
