# CMakeList.txt : CMake project for ex10, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(pybind11_module_example)

# Set source directory
set(SOURCE_DIR "python_cpp_example")


# Tell CMake that headers are also in SOURCE_DIR
include_directories(${SOURCE_DIR})
set(SOURCES "${SOURCE_DIR}/PopRace.h")

add_subdirectory(pybind11-master)
pybind11_add_module(pybind11_module_example ${SOURCES} "${SOURCE_DIR}/bindings.cpp")