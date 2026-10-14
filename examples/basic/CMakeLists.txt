cmake_minimum_required(VERSION 3.12...3.27.4)

set(CMAKE_CXX_STANDARD 20)

project(basic_example)
add_executable(basic_example basic.cpp)
target_link_libraries(basic_example PUBLIC teel_error)
