cmake_minimum_required(VERSION 3.16)
project(KhachHang C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(../Utils)

add_executable(KhachHang KhachHang_test.c KhachHang.c ../Utils/Utils.c)
