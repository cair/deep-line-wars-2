
#include <pybind11/embed.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_actions(py::module &);
void init_attack(py::module &);
void init_constants(py::module &);
void init_entity(py::module &);
void init_game(py::module &);
void init_map(py::module &);
void init_player(py::module &);
void init_shop(py::module &);
void init_tile(py::module &);
void init_config(py::module &);
void init_mechanic(py::module &);
void init_discrete_actions(py::module &);
//void init_gui(py::module &);

PYBIND11_MODULE(Engine, m) {
m.doc() = "DeepLineWars Engine";
init_actions(m);
init_attack(m);
init_constants(m);
init_entity(m);
init_game(m);
init_map(m);
init_player(m);
init_shop(m);
init_tile(m);
init_config(m);
init_mechanic(m);
init_discrete_actions(m);
//init_gui(m);
}
