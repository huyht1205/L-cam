include("cmake/arm-none-eabi-gcc.cmake")

enable_language(ASM C CXX)

add_compile_options(
    -Og
    -Wall
    -fdata-sections
    -ffunction-sections
    -g -gdwarf-2
    )

# Suspended warnings
add_compile_options(
    -Wno-unused-function
    -Wno-unused-parameter
    -Wno-sign-compare
    -Wno-switch
    -Wno-strict-aliasing
    )

# For C++
add_compile_options(
    -fno-exceptions # Remove exception to save FLASH
    -fstack-usage
    )

add_compile_options(
    $<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>
    )

add_compile_options(
    $<$<COMPILE_LANGUAGE:CXX>:-std=gnu++20>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-use-cxa-atexit>
    $<$<COMPILE_LANGUAGE:CXX>:-Wno-volatile>
    )

add_compile_options(
    $<$<COMPILE_LANGUAGE:C>:-std=gnu99>
    )

add_link_options(
    -specs=nano.specs
    -Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_NAME}.map
    -specs=nosys.specs
    -specs=nano.specs
    -Xlinker
    -lc
    -lm
    -lstdc++
    -lsupc++
    )


function(post_build TARGET)
    add_custom_target(${TARGET}.bin ALL
        DEPENDS ${TARGET}.elf
        COMMAND ${CMAKE_OBJCOPY} -Obinary ${TARGET}.elf ${TARGET}.bin
        COMMAND ${CMAKE_OBJCOPY} -Oihex ${TARGET}.elf ${TARGET}.hex
        COMMENT "Building ${TARGET}.hex and ${TARGET}.bin")
endfunction()

macro(print_all_variables)
message(STATUS "print_all_variables------------------------------------------{")
get_cmake_property(_variableNames VARIABLES)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()
message(STATUS "print_all_variables------------------------------------------}")
endmacro()