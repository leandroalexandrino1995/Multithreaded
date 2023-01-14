cmake_minimum_required(VERSION 3.5.1)

project(MultiThreadQueue)

set(EXEC MultiThreadQueue)

set(CMAKE_CXX_STANDARD 14)

include_directories(inc)

file(GLOB SOURCES src/*.cpp)

add_executable(${EXEC} ${SOURCES})
