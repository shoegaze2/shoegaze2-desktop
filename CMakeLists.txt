cmake_minimum_required(VERSION 3.1)
project(shoegaze2-desktop)

set(DEPS_DIR ${CMAKE_CURRENT_LIST_DIR}/deps)
add_executable(shoegaze2-desktop src/main.cpp)

add_subdirectory(src/shoegaze2)

target_link_libraries(shoegaze2-desktop PUBLIC shoegaze2-desktop-lib)