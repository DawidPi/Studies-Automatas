cmake_minimum_required(VERSION 3.7)
project(CLionProjectsAutomata)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp TransitionTable.hpp Automata.hpp)
add_executable(CLionProjectsAutomata ${SOURCE_FILES})