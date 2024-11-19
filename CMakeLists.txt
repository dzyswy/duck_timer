cmake_minimum_required(VERSION 3.8)
project(duck_timer)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package (glog REQUIRED)

include_directories(./)

file(GLOB_RECURSE SOURCES "timer/*.cpp" "utils/*.cpp")

add_executable(main ${SOURCES} main.cpp)
target_link_libraries (main glog::glog)
 

add_executable(timer_manager_demo ${SOURCES} timer_manager_demo.cpp)
target_link_libraries (timer_manager_demo glog::glog)










