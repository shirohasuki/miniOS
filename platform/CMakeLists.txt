add_library(platform OBJECT
  ch32v307/uart.c
  ch32v307/pfic.c
  ch32v307/timer.c
  ch32v307/rcc.c
  ch32v307/csr.S

  device/stdbuff.c
)

target_include_directories(platform PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/platform/ch32v307
  ${CMAKE_SOURCE_DIR}/platform/device
) 