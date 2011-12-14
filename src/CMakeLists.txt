set(xo_src main.c terminal.c monitorbuffer.c)
link_libraries(pthread)

add_executable (xo ${xo_src})
