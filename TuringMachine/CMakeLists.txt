project(TuringMachine)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES main.cpp Tape.hpp TuringMachineTransitionTable.hpp TuringMachine.hpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ./)
