project(tests)

add_subdirectory(lib/googletest-release-1.8.0)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(run_tests
        ResourceTest.cpp)

target_link_libraries(run_tests gtest gtest_main)
target_link_libraries(run_tests ga_lib_shared)
