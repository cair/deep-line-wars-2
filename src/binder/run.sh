#!/bin/bash

cd /data

mkdir -p cmake-make && cd cmake-make && cmake ..
make -j
binder \
--root-module my_project \
--bind my_root_namespace binder_includes.hpp \
-- -std=c++17 \
-Iinclude/cpptoml/include \
-Iinclude/cpptoml/include
