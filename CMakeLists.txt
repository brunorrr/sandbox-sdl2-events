cmake_minimum_required(VERSION 3.20)

project(sandbox-sdl2-events LANGUAGES CXX)

find_package(SDL2 CONFIG REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)