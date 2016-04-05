cmake_minimum_required(VERSION 3.5)
project(MS_RCPSP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    include/Algorithm.h
    include/Crossover.h
    include/Mutator.h
    include/Population.h
    include/Project.h
    include/ProjectReader.h
    include/Random.h
    include/Schedule.h
    include/Selector.h
    include/Task.h
    src/Algorithm.cpp
    src/Crossover.cpp
    src/Mutator.cpp
    src/Population.cpp
    src/Project.cpp
    src/ProjectReader.cpp
    src/Random.cpp
    src/Schedule.cpp
    src/Selector.cpp
    src/Task.cpp
    main.cpp)

add_executable(MS_RCPSP ${SOURCE_FILES})