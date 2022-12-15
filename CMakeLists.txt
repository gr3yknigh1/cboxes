cmake_minimum_required(VERSION 3.22)
project(c-linkedlist C)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE PROJECT_SOURCES src/*.c)
add_executable(${PROJECT_NAME} src/main.c)
target_compile_options(${PROJECT_NAME} PRIVATE -g)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})

