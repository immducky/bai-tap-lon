cmake_minimum_required(VERSION 3.16)
project(BaiTapLon)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(./Utils)
include_directories(./KhachHang)
include_directories(./GiaDien)
include_directories(./ChiSoDien)

add_executable(BaiTapLon main.c ./ChiSoDien/ChiSoDien.c ./GiaDien/GiaDien.c ./KhachHang/KhachHang.c ./Utils/Utils.c)

target_link_libraries(BaiTapLon m)
