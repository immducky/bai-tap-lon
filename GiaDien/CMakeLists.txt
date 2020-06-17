cmake_minimum_required(VERSION 3.16)
project(GiaDien C)

set(CMAKE_C_STANDARD 99)

add_executable(GiaDien GiaDien.c GiaDien_test.c ../Utils/Utils.c GiaDien_test.c)