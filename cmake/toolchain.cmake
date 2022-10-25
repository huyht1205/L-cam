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
    -fno-rtti # Remove RTTI (dynamic_cast) to save FLASH
    )

add_compile_options($<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>)

add_link_options(
    ${C_OPTS_MCU}
    -specs=nano.specs
    -Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_NAME}.map
    -specs=nosys.specs
    -specs=nano.specs
    -Xlinker
    # -Wl,--defsym=malloc_getpagesize_P=0x80
    -lc -lm -lnosys
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