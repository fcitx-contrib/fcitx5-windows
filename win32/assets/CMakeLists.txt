set(PENGUIN_SVG "${CMAKE_CURRENT_SOURCE_DIR}/penguin.svg")
set(PENGUIN_ICO "${PROJECT_BINARY_DIR}/dll/penguin.ico")
add_custom_command(
    OUTPUT "${PENGUIN_ICO}"
    COMMAND magick -background none "${PENGUIN_SVG}" "${PENGUIN_ICO}"
    DEPENDS "${PENGUIN_SVG}"
)
add_custom_target(GenerateIco ALL
    DEPENDS "${PENGUIN_ICO}"
)
