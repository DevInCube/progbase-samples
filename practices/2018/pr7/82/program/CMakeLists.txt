cmake_minimum_required(VERSION 3.0.0)

project(a.out)

include_directories(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/../library)
link_directories(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/../library/build)

file(GLOB SOURCES "*.c")

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} mymap)