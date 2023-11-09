cmake_minimum_required(VERSION 3.26)
project(typereflect)

set(CMAKE_CXX_STANDARD 17)

add_executable(typereflect main.cpp
        dtc/Type.h
        dtc/Variable.h
        dtc/Type.cpp
        dtc/Variable.cpp
        dtc/VarMath.cpp
        dtc/VarMath.h)
