cmake_minimum_required(VERSION 3.0.0)

project(mymap)

file(GLOB SOURCES "*.c")

add_library(${PROJECT_NAME} STATIC ${SOURCES})