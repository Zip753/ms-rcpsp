cmake_minimum_required(VERSION 3.5)
project(ms-rcpsp)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif(NOT CMAKE_BUILD_TYPE)

add_definitions(-std=c++14)

file(GLOB_RECURSE srcs "src/*.cpp")

add_library(ms_rcpsp_objects OBJECT ${srcs})
add_library(ms_rcpsp_static STATIC $<TARGET_OBJECTS:ms_rcpsp_objects>)
add_library(ms_rcpsp_shared SHARED ${srcs})

add_subdirectory(lib)

add_executable(ms_rcpsp $<TARGET_OBJECTS:ms_rcpsp_objects> ms_rcpsp.cpp)
target_link_libraries(ms_rcpsp gflags)

set_target_properties(ms_rcpsp_static ms_rcpsp_shared ms_rcpsp
        PROPERTIES
        "ARCHIVE_OUTPUT_DIRECTORY" "${CMAKE_BINARY_DIR}/lib"
        "LIBRARY_OUTPUT_DIRECTORY" "${CMAKE_BINARY_DIR}/lib"
        "RUNTIME_OUTPUT_DIRECTORY" "${CMAKE_BINARY_DIR}/bin"
)

add_subdirectory(tests)
add_subdirectory(visualization)
