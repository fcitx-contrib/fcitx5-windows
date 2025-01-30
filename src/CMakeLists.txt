add_executable(Fcitx5 main.cpp)
target_link_libraries(Fcitx5 Fcitx5::Core)

install(TARGETS Fcitx5 DESTINATION "${FCITX_INSTALL_BINDIR}")
