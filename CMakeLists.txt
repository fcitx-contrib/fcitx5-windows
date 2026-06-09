cmake_minimum_required(VERSION 3.27)

project(fcitx5-windows VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)

option(ENABLE_TESTING_ADDONS "" OFF)
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
option(BUILD_SPELL_DICT "" OFF)

set(CMAKE_INSTALL_PREFIX C:)
set(ENV{PKG_CONFIG_PATH} "${CMAKE_SYSROOT}/lib/pkgconfig")
# For std::osyncstream
add_compile_options(-fexperimental-library)

add_subdirectory(fcitx5)
target_compile_definitions(Fcitx5Utils PUBLIC -DFcitx5Utils_EXPORTS)
target_compile_definitions(Fcitx5Core PUBLIC -DFcitx5Core_EXPORTS)

add_subdirectory(src)
