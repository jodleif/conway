cmake_minimum_required(VERSION 3.3)
project(conway)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic")

set(SOURCE_FILES main.cpp game_logic/gol.cpp console_gfx/console_gfx.cpp console_gfx/console_gfx.h)
add_executable(conway ${SOURCE_FILES})