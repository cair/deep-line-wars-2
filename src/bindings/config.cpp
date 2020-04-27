
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../config/config.h"

namespace py = pybind11;

void init_config(py::module &m) {
    py::class_<config>(m, "config")
        .def(py::init<>())
        .def_readwrite("mechanics", &config::mechanics)
        .def_readwrite("startHealth", &config::startHealth)
        .def_readwrite("startGold", &config::startGold)
        .def_readwrite("startLumber", &config::startLumber)
        .def_readwrite("startIncomeGold", &config::startIncomeGold)
        .def_readwrite("incomeFrequency", &config::incomeFrequency)
        .def_readwrite("incomeRatio", &config::incomeRatio)
        .def_readwrite("killGoldRatio", &config::killGoldRatio)
        .def_readwrite("enemyTerritoryDecay", &config::enemyTerritoryDecay)
        .def_readwrite("friendlyTerritoryDecay", &config::friendlyTerritoryDecay)
        .def_readwrite("ticksPerSecond", &config::ticksPerSecond)
        .def_readwrite("fps", &config::fps)
        .def_readwrite("ups", &config::ups);

}
