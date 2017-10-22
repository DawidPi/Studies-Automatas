project(Automata)

set(CMAKE_CXX_STANDARD 14)

set(HEADERS
        ${PROJECT_SOURCE_DIR}/Automata.hpp
        ${PROJECT_SOURCE_DIR}/TransitionTable.hpp)

add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME} INTERFACE ${HEADERS})
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_SOURCE_DIR})