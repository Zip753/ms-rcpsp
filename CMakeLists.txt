cmake_minimum_required(VERSION 3.5)
project(ms-rcpsp)

file(GLOB_RECURSE srcs "src/*.cpp")
file(GLOB_RECURSE hdrs "include/*.h")

set(SOURCE_FILES ${srcs} ${hdrs} main.cpp)

include_directories(/usr/include/gflags)

add_executable(ga_bin ${SOURCE_FILES})
target_link_libraries(ga_bin /usr/lib/x86_64-linux-gnu/libgflags.so)

add_definitions(-std=c++14)
