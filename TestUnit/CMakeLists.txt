cmake_minimum_required(VERSION 3.5.1)

project(QueueTestUnit)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
add_executable(TestQueue TestQueue.cpp)
target_link_libraries(TestQueue ${GTEST_LIBRARIES} pthread)
