cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_FLAGS "-g")
project(ALOP)
add_library( ALOP STATIC inc/tri-diag-matrix.cpp )

