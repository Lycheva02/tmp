cmake_minimum_required(VERSION 3.10)
project(exc)

set(GTEST_ROOT /usr/lib)

find_package(GTest REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE GTest::GTest GTest::Main)