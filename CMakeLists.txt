cmake_minimum_required(VERSION 3.18)

project(BMPtoASCII VERSION 0.3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-O3)

add_executable(BMPtoASCII src/main.cpp src/bmp/bmp_file.cpp)
target_include_directories(BMPtoASCII PRIVATE src/bmp/include)