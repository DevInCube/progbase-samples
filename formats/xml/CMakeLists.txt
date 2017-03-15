cmake_minimum_required(VERSION 2.8.9)
project (xmlproj)

include_directories(include /usr/include/libxml2)
file(GLOB SOURCES "src/*.c")

add_executable(${CMAKE_PROJECT_NAME} main.c)
target_link_libraries(${CMAKE_PROJECT_NAME} xml2 )
