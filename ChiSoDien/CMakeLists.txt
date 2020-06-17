cmake_minimum_required(VERSION 3.16)
project(ChiSoDien C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(../Utils)

add_executable(ChiSoDien ChiSodien.c ChiSoDien_test.c ../Utils/Utils.c)