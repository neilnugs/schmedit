cmake_minimum_required(VERSION 3.10.0)
project(schmedit VERSION 0.1.0 LANGUAGES C CXX)

add_executable(schmedit src/main.cpp)

include(CTest)
enable_testing()

