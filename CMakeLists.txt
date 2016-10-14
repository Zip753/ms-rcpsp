cmake_minimum_required(VERSION 3.5)
project(ms-rcpsp)

file(GLOB_RECURSE srcs "src/*.cpp")
file(GLOB_RECURSE hdrs "include/*.h")

set(SOURCE_FILES ${srcs} ${hdrs})

add_subdirectory(gflags)

add_library(ga_lib ${SOURCE_FILES})

add_executable(ga_bin ${SOURCE_FILES} main.cpp)
target_link_libraries(ga_bin gflags)

set_target_properties(ga_lib ga_bin
        PROPERTIES
        "ARCHIVE_OUTPUT_DIRECTORY" "${CMAKE_BINARY_DIR}/lib"
        "LIBRARY_OUTPUT_DIRECTORY" "${CMAKE_BINARY_DIR}/lib"
        "RUNTIME_OUTPUT_DIRECTORY" "${CMAKE_BINARY_DIR}/bin"
)

add_definitions(-std=c++14)
