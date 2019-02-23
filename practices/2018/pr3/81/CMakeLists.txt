cmake_minimum_required(VERSION 2.8.9)

project(a.out)

include_directories(include)

file(GLOB CSOURCES "*.c")
file(GLOB SRCSOURCES "src/*.c")

add_executable(${PROJECT_NAME} ${CSOURCES} ${SRCSOURCES})

target_link_libraries(${PROJECT_NAME} progbase)

SET(CMAKE_C_FLAGS "-std=c11 -Wall -pedantic-errors -Werror -Wno-unused")

