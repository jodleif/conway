cmake_minimum_required(VERSION 3.3)
project(conway)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic -lncurses ")

set(SOURCE_FILES main.cpp game_logic/gol.cpp game_logic/gol.h console_gfx/screen.cpp console_gfx/screen.h console_gfx/frame.cpp console_gfx/frame.h game/game.cpp game/game.h)
add_executable(conway ${SOURCE_FILES})
