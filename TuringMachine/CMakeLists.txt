project(TuringMachine)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES main.cpp Tape.hpp TuringMachineTransitionTable.hpp TurinMachine.hpp)

add_executable(${PROJECT_NAME} ${SOURCES})
