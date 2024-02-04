cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_FLAGS "-g")
project(main)

add_executable(main src/main.cpp)

target_include_directories(main PRIVATE ../inc)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

target_link_directories(main PUBLIC ../build)
target_link_libraries(main alineofpotatoes ${GTEST_LIBRARIES} pthread)

