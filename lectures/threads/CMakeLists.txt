cmake_minimum_required(VERSION 2.8.9)

include_directories(include)
file(GLOB LIB_SOURCES "src/*.cpp")

project(a.out)
# to build executable target with name a.out
add_executable(${CMAKE_PROJECT_NAME} "main.cpp" ${LIB_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} m pthread progbase-cpp progbase)
