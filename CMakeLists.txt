cmake_minimum_required(VERSION 3.27)

project(fcitx5-windows VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)

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
option(BUILD_SPELL_DICT "" ${CYGWIN})

if (CYGWIN)
    set(CMAKE_INSTALL_PREFIX /usr)
    set(ECM_DIR /clang64/share/ECM/cmake)
    add_compile_definitions(-D_GNU_SOURCE)
else()
    set(CMAKE_INSTALL_PREFIX C:)
    set(ENV{PKG_CONFIG_PATH} "${CMAKE_SYSROOT}/lib/pkgconfig")
endif()

add_subdirectory(fcitx5)
target_compile_definitions(Fcitx5Utils PUBLIC -DFcitx5Utils_EXPORTS)
target_compile_definitions(Fcitx5Core PUBLIC -DFcitx5Core_EXPORTS)

if (CYGWIN)
    # exe needs dll in the same directory.
    set(FCITX5UTILS_DLL_NAME msys-Fcitx5Utils-2.dll)
    set(FCITX5UTILS_COPY "${PROJECT_BINARY_DIR}/fcitx5/src/modules/spell/${FCITX5UTILS_DLL_NAME}")
    add_custom_command(
        OUTPUT "${FCITX5UTILS_COPY}"
        DEPENDS Fcitx5Utils
        COMMAND cp "$<TARGET_FILE:Fcitx5Utils>" "${FCITX5UTILS_COPY}"
    )
    add_custom_target(copy_fcitx5utils ALL DEPENDS "${FCITX5UTILS_COPY}")
    add_dependencies(spell_en_dict copy_fcitx5utils)
endif()

add_subdirectory(src)
