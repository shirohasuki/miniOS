add_library(kernel OBJECT
  start.S
  kernel.c
  user.c

  mem/mem.S
  mem/page.c

  context/sched.c
  context/entry.S

  # csr/csr.c
  # csr/csr.S

  trap/trap.c
  trap/trap.S

  test/page_test.c 
  test/task_test.c
  test/exception_test.c
  test/external_interrupt_test.c
  test/preemptive_task_test.c
)

target_include_directories(kernel PRIVATE
  ${CMAKE_SOURCE_DIR}/src/kernel
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src/kernel/include
  ${CMAKE_SOURCE_DIR}/platform
  ${CMAKE_SOURCE_DIR}/minilib
) 