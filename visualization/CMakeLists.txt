file(GLOB visualization_srcs *.cc)
file(GLOB visualization_hdrs *.h)

add_executable(visualize ${visualization_srcs} ${visualization_hdrs})
target_link_libraries(visualize ga_static)
