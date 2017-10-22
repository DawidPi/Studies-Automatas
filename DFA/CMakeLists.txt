project(DFA)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} Automata)