set(xo_src canvas.c main.c monitorbuffer.c terminal.c utils.c xo.c)

link_libraries(bsd)
link_libraries(pthread)

add_executable (xo ${xo_src})
