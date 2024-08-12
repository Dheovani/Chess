cmake_minimum_required(VERSION 3.10)
project(ChessGame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
add_executable(ChessGame main.cpp game.h game.cpp piece.h)

target_link_libraries(ChessGame PRIVATE sfml-system sfml-window sfml-graphics OpenGL::GL)