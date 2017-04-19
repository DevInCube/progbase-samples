cmake_minimum_required(VERSION 2.8.9)

project(a.out)
# to build executable target with name a.out
add_executable(${CMAKE_PROJECT_NAME} "main.cpp" ${LIB_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} progbase-cpp progbase)
