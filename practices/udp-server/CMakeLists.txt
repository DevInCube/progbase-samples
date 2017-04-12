cmake_minimum_required(VERSION 2.8.9)

#
# Common settings
#

# adds ./include to compiler include directories
include_directories(include)
#
# Second project (executable)
#
project(server)
add_executable(${CMAKE_PROJECT_NAME} "server.c")
target_link_libraries(${CMAKE_PROJECT_NAME} progbase)
#
# Second project (executable)
#
project(client)
add_executable(${CMAKE_PROJECT_NAME} "client.c")
target_link_libraries(${CMAKE_PROJECT_NAME} progbase)
