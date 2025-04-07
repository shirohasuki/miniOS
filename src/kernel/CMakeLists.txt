add_library(kernel OBJECT
  start.S
  kernel.c
)

set_source_files_properties(start.S PROPERTIES
  LANGUAGE ASM
)

target_include_directories(kernel PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/platform
) 