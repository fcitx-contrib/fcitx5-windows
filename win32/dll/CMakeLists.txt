add_library(fcitx5-x86_64 SHARED
    main.cpp
    register.cpp
    util.cpp
)

target_compile_options(fcitx5-x86_64 PRIVATE "-Wno-dll-attribute-on-redeclaration")

target_link_libraries(fcitx5-x86_64 tsf)
