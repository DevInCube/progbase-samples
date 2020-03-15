cmake_minimum_required(VERSION 3.6)

project(ruslan)

include_directories(.)
file(GLOB SOURCES "*.cpp")

#Generate the shared (STATIC, SHARED or MODULE) library from the sources
add_library(${PROJECT_NAME} STATIC ${SOURCES})

# install library headers
install(
    DIRECTORY      ./     
    DESTINATION    /usr/local/include/ruslan
    FILES_MATCHING PATTERN "*.h"
    PATTERN "build" EXCLUDE
)

#Set the location for library installation -- i.e., /usr/local/lib in this case
# not really necessary in this example. Use "sudo make install" to apply
install(
    TARGETS     ${PROJECT_NAME} 
    DESTINATION /usr/local/lib
)
