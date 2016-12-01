include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB srcs "*.cpp")

add_executable(scheduling_tests ${srcs})

target_link_libraries(scheduling_tests gtest gtest_main)
target_link_libraries(scheduling_tests ms_rcpsp_static)
