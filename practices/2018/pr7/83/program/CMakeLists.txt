cmake_minimum_required(VERSION 3.0.0)

project(a.out)

include_directories(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/../library)
link_directories(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/../library/build)

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} mymap)