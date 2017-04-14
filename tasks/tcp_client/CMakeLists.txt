cmake_minimum_required(VERSION 2.8.7)

project (a.out)
add_executable(${CMAKE_PROJECT_NAME} "main.c")
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY C_STANDARD 99)
target_link_libraries(${CMAKE_PROJECT_NAME} progbase)

SET(CMAKE_C_FLAGS "-std=c99 -Werror -Wall")
