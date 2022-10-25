# specify cross-compilers and tools
# If the Path is "" (Empty) then cmake tries to auto-detect.
set(TOOLCHAIN_PATH "/Users/hoanghuy/gcc-arm-none-eabi-10.3-2021.10/bin")

add_compile_options(
    -isystem ${TOOLCHAIN_PATH}/../arm-none-eabi/include
)
