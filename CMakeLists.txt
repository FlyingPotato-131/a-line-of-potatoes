cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_FLAGS "-g")
project(alineofpotatoes)
add_library( alineofpotatoes STATIC inc/tri-diag-matrix.cpp )

