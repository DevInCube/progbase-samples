cmake_minimum_required(VERSION 2.8.9)
project (xmlproj)
add_executable(xmlproj main.c)

include_directories(include /usr/include/libxml2)
file(GLOB SOURCES "src/*.c")

set ( PROJECT_LINK_LIBS libxml2.so )
target_link_libraries(xmlproj ${PROJECT_LINK_LIBS} )