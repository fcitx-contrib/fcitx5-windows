function(add_test_target TARGET_NAME)
    add_executable(${TARGET_NAME} ${ARGN})
    # Enable assert for release build.
    target_compile_options(${TARGET_NAME} PRIVATE -UNDEBUG)
    add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
endfunction()

add_test_target(test_dll test_dll.cpp ../dll/util.cpp)
