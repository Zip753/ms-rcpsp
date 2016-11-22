file(GLOB srcs *.cc)
file(GLOB hdrs *.h)

add_executable(visualize ${srcs} ${hdrs})
