add_library(platform OBJECT
  ch32v307/uart.c
)

target_include_directories(platform PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/platform/ch32v307
) 