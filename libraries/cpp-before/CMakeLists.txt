cmake_minimum_required(VERSION 3.6)

project(a.out)

file(GLOB SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})