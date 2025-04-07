cmake_minimum_required(VERSION 3.10)

project(miniOS LANGUAGES C ASM)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostdlib -fno-builtin -march=rv32imac_zicsr -mabi=ilp32 -g -Wall")
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS}")

set(CMAKE_C_COMPILER riscv64-unknown-elf-gcc)
set(CMAKE_ASM_COMPILER riscv64-unknown-elf-gcc)
set(CMAKE_OBJCOPY riscv64-unknown-elf-objcopy)
set(CMAKE_OBJDUMP riscv64-unknown-elf-objdump)

add_subdirectory(src/kernel)
add_subdirectory(platform)

add_executable(os.elf
  $<TARGET_OBJECTS:kernel>
  $<TARGET_OBJECTS:platform>
)

set_target_properties(os.elf PROPERTIES
  LINK_FLAGS "-Ttext=0x00000000"
)

add_custom_command(TARGET os.elf POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O binary os.elf os.bin
  COMMAND ${CMAKE_OBJCOPY} -O ihex os.elf os.hex
  COMMENT "Generate binary and hex file"
)

add_custom_target(flash
  COMMAND openocd -f openocd.cfg -c init -c halt -c "program os.bin" -c exit
  DEPENDS os.elf
  COMMENT "Flashing os.bin to board"
)

add_custom_target(code
  COMMAND ${CMAKE_OBJDUMP} -S os.elf | less
  DEPENDS os.elf
  COMMENT "Disassembling os.elf"
) 