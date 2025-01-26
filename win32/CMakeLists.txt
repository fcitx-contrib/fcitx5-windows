cmake_minimum_required(VERSION 3.27)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project(fcitx5-win32 VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(assets)
add_subdirectory(tsf)
add_subdirectory(dll)

enable_testing()
add_subdirectory(tests)
