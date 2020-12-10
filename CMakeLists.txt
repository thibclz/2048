
cmake_minimum_required(VERSION 3.0.0)
project(2048)


include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(2048 ${SOURCES})
