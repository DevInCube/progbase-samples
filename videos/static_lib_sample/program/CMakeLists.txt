cmake_minimum_required(VERSION 3.0.0)

project(a.out)

file(GLOB SOURCES "*.c")

include_directories(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/../mygraphics)
link_directories(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/../mygraphics/build)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} mygraphics m)