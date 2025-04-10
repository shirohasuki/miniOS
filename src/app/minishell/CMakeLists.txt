add_library(minishell OBJECT
  busybox.c
  shell.c
  readline/readline.c
)

target_include_directories(minishell PRIVATE
  ${CMAKE_SOURCE_DIR}/minilib
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src/app/minishell/resource
  ${CMAKE_SOURCE_DIR}/src/app/minishell/include
  ${CMAKE_SOURCE_DIR}/src/kernel/include
  ${CMAKE_SOURCE_DIR}/platform
) 
