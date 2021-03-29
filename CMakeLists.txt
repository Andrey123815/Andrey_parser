cmake_minimum_required(VERSION 3.16)
project(dz-4)

set(CMAKE_C_FLAGS "-pedantic")
set(CMAKE_CXX_FLAGS "-pedantic")

# <Source>
include_directories("include")

file(GLOB sources
        "include/*.h"
        "src/*.c")
# </Source>


add_executable(dz-4 ${sources})

# <SOURCE_DIR>
add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
# </SOURCE_DIR>