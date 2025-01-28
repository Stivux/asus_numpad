cmake_minimum_required(VERSION 3.13)

project(asus_numpad_tests)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory("${CMAKE_SOURCE_DIR}/extern/googletest" "extern/googletest")
link_libraries(gtest_main)

add_executable(utils_test
        utils_tests.cpp
        ../src/utils.cpp
)

gtest_discover_tests(utils_test)