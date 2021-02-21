cmake_minimum_required(VERSION 3.5)

set(This Lab6_with_tests)
project(${This})

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

enable_testing()
include_directories(src)


add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)