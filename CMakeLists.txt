cmake_minimum_required(VERSION 3.16)
project(fortuneAvenueDev)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Nombre del ejecutable final
set(EXECUTABLE_NAME fortuneAvenue)

# Archivos fuente
file(GLOB_RECURSE SOURCES src/*.cpp src/*.hpp)

# Incluir encabezados desde src y SFML
include_directories(src)
include_directories(external/sfml/include)

# Agregar ruta a las bibliotecas SFML
link_directories(${CMAKE_SOURCE_DIR}/external/sfml/lib)

# ENet (subdirectorio con su CMakeLists.txt)
add_subdirectory(external/enet)

# Crear ejecutable
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Enlazar SFML y ENet
target_link_libraries(${EXECUTABLE_NAME}
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
    sfml-network
    enet
)

# En Windows, agregar libs del sistema
if(WIN32)
    target_link_libraries(${EXECUTABLE_NAME} winmm ws2_32 opengl32)
endif()

# En Linux, agregar hilo
if(UNIX AND NOT APPLE)
    find_package(Threads REQUIRED)
    target_link_libraries(${EXECUTABLE_NAME} Threads::Threads)
endif()
