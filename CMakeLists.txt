cmake_minimum_required(VERSION 3.27)

project(game)

set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(SFML_LIB_DIR "${PROJECT_SOURCE_DIR}/deps/SFML-2.6.2/lib")
set(SFML_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/deps/SFML-2.6.2/include")

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_DIR}/main.cpp 
                                     ${SOURCE_DIR}/player.cpp 
                                     ${SOURCE_DIR}/drop.cpp
                                     ${SOURCE_DIR}/bullet.cpp
                                     ${SOURCE_DIR}/enemy.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${SFML_INCLUDE_DIR})
target_link_directories(${CMAKE_PROJECT_NAME} PUBLIC ${SFML_LIB_DIR})
target_link_libraries(${CMAKE_PROJECT_NAME} sfml-graphics sfml-system sfml-window)