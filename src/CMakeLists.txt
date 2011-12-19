set(xo_src buffer.c canvas.c main.c terminal.c utils.c xo.c)

link_libraries(pthread)

add_executable (xo ${xo_src})
