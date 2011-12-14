set(xo_src main.c utils.c monitorbuffer.c)
link_libraries(pthread)

add_executable (xo ${xo_src})
