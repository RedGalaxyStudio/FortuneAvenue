cmake_minimum_required(VERSION 3.10)

project(enet)

add_library(enet STATIC
    list.c
    compress.c
    host.c
    peer.c
    protocol.c
    win32.c  # Usa unix.c si estás compilando en Linux (aunque no lo necesitas si usas ENet del sistema)
)

target_include_directories(enet PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
