cmake_minimum_required(VERSION 3.13)
project(asus_numpad)
set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp)

option(PACKAGE_TESTS "Build the tests" OFF)

if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif()

target_sources(${PROJECT_NAME} PRIVATE
        src/utils.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)

find_package(PkgConfig REQUIRED)
pkg_search_module(LIBEVDEV REQUIRED libevdev)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${LIBEVDEV_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBEVDEV_LIBRARIES})

set(${PROJECT_NAME}_POSSIBLE_INCLUDE_DEFINES
        INCLUDE_UP5401EA INCLUDE_B7402
)

set(${PROJECT_NAME}_DEFINED_INCLUDES "")
foreach (DEFINE ${${PROJECT_NAME}_POSSIBLE_INCLUDE_DEFINES})
    if (${DEFINE})
        list(APPEND ${PROJECT_NAME}_DEFINED_INCLUDES ${DEFINE})
    endif ()
endforeach ()

if (${PROJECT_NAME}_DEFINED_INCLUDES)
    target_compile_definitions(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_DEFINED_INCLUDES})
else ()
    target_compile_definitions(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_POSSIBLE_INCLUDE_DEFINES})
endif ()

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address)
    target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address)
endif ()