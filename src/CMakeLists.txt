set(xo_src canvas.c main.c monitorbuffer.c terminal.c)
link_libraries(pthread)

add_executable (xo ${xo_src})
