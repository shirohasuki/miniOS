add_library(minilib OBJECT
  printf.c
  string.c
)

target_include_directories(minilib PUBLIC
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/platform
) 
