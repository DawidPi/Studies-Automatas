project(NFA)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} Automata)