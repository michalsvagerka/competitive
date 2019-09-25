cmake_minimum_required(VERSION 2.8.4)
project(majk)

add_executable(output output/main.cpp)
add_executable(testrunner testrunner/main.cpp)
file(GLOB TASKS "tasks/*.cpp")
file(GLOB_RECURSE HEADERS "l/*.h" )

ADD_DEFINITIONS(-std=c++17)
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-stack_size -Wl,0x16000000")

add_executable(test ${TASKS} ${HEADERS})
