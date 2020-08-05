cmake_minimum_required(VERSION 3.15)
project(Shellz)

set(CMAKE_CXX_STANDARD 17)

add_executable(Shellz main.cpp utils.h src/definitions.h src/Command.cpp src/Command.h src/Field.cpp src/Field.h src/index.h)