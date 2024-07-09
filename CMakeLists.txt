cmake_minimum_required(VERSION 3.10)

project(Astronaut)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    main.cpp
    astronaut.cpp
    flight.cpp
    utils.cpp
)

set(HEADERS
    astronaut.h
    flight.h
    utils.h
)

add_executable(Astronaut ${SOURCES})

