cmake_minimum_required(VERSION 3.27)

project(fcitx5-windows VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

option(ENABLE_TEST "" OFF)
option(ENABLE_COVERAGE "" OFF)
option(ENABLE_ENCHANT "" OFF)
option(ENABLE_X11 "" OFF)
option(ENABLE_WAYLAND "" OFF)
option(ENABLE_DBUS "" OFF)
option(ENABLE_DOC "" OFF)
option(ENABLE_SERVER "" OFF)
option(ENABLE_KEYBOARD "" OFF)
option(USE_SYSTEMD "" OFF)
option(ENABLE_XDGAUTOSTART "" OFF)
option(ENABLE_EMOJI "" OFF)
option(ENABLE_LIBUUID "" OFF)

set(ECM_DIR /ucrt64/share/ECM/cmake)
add_definitions(-DFcitx5Core_EXPORTS -DFcitx5Utils_EXPORTS -D_GNU_SOURCE)
add_subdirectory(fcitx5)
