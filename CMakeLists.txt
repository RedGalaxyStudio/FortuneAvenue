cmake_minimum_required(VERSION 3.16)
project(fortuneAvenueDev)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Nombre del ejecutable final
set(EXECUTABLE_NAME fortuneAvenue)

# Archivos fuente
file(GLOB_RECURSE SOURCES FortuneAvenueDev/src/*.cpp FortuneAvenueDev/src/*.hpp)

# Incluir encabezados desde src
include_directories(src)

# Incluir SFML
if(WIN32)
    include_directories(external/SFML-2.6.2/include)
    link_directories(${CMAKE_SOURCE_DIR}/external/SFML-2.6.2/lib)
else()
    find_package(SFML 2.5 COMPONENTS graphics window system audio network REQUIRED)
endif()

# ENet
if(WIN32)
    include_directories(external/Enet/include)
    add_subdirectory(${CMAKE_SOURCE_DIR}/external/Enet/lib)  # Asegúrate que tenga un CMakeLists.txt
    set(ENET_LIB enet)
else()
    find_library(ENET_LIB enet REQUIRED)
    include_directories(/usr/include)
endif()

# Crear ejecutable
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Enlazar SFML
if(WIN32)
    target_link_libraries(${EXECUTABLE_NAME}
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        sfml-network
    )
else()
    target_link_libraries(${EXECUTABLE_NAME}
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        sfml-network
    )
endif()

# Enlazar ENet
target_link_libraries(${EXECUTABLE_NAME} ${ENET_LIB})

# En Windows, agregar libs del sistema
if(WIN32)
    target_link_libraries(${EXECUTABLE_NAME} winmm ws2_32 opengl32)
endif()

# En Linux, agregar hilo
if(UNIX AND NOT APPLE)
    find_package(Threads REQUIRED)
    target_link_libraries(${EXECUTABLE_NAME} Threads::Threads)
endif()
