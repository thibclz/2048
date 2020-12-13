cmake_minimum_required(VERSION 3.0.0)
project(2048 VERSION 0.1.0)

include(CTest)
enable_testing()



include_directories(include)

set(SOURCES src/internals.cpp src/Board.cpp src/Line.cpp src/Display.cpp include/internals.h include/Board.h include/Line.h include/Display.h)

add_executable(2048 main.cpp ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
