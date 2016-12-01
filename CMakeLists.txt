cmake_minimum_required(VERSION 3.5)
project(ms-rcpsp)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif(NOT CMAKE_BUILD_TYPE)

add_definitions(-std=c++14)

file(GLOB_RECURSE srcs "src/*.cpp")

add_library(ga_objects OBJECT ${srcs})
add_library(ga_static STATIC $<TARGET_OBJECTS:ga_objects>)
add_library(ga_shared SHARED ${srcs})

add_subdirectory(lib)

add_executable(ga_bin $<TARGET_OBJECTS:ga_objects> ms_rcpsp.cpp)
target_link_libraries(ga_bin gflags)

set_target_properties(ga_static ga_shared ga_bin
        PROPERTIES
        "ARCHIVE_OUTPUT_DIRECTORY" "${CMAKE_BINARY_DIR}/lib"
        "LIBRARY_OUTPUT_DIRECTORY" "${CMAKE_BINARY_DIR}/lib"
        "RUNTIME_OUTPUT_DIRECTORY" "${CMAKE_BINARY_DIR}/bin"
)

add_subdirectory(tests)
add_subdirectory(visualization)
