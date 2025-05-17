cmake_minimum_required(VERSION 3.10)

project(enet)

if(WIN32)
    include_directories(${CMAKE_SOURCE_DIR}/../include)
    link_directories(${CMAKE_SOURCE_DIR}/../lib)
endif()

target_include_directories(enet PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
