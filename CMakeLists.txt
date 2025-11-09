cmake_minimum_required(VERSION 3.20)
project(FortuneAvenueDev LANGUAGES CXX)

# --- Configuración del compilador ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)

# --- Nombre del ejecutable ---
set(EXECUTABLE_NAME fortuneAvenue)

# --- Archivos fuente ---
file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/FortuneAvenueDev/src/*.cpp
    ${CMAKE_SOURCE_DIR}/FortuneAvenueDev/src/*.hpp
)

# --- Incluir encabezados ---
include_directories(${CMAKE_SOURCE_DIR}/FortuneAvenueDev/src)

# --- Dependencias GTK (solo Linux) ---
if(UNIX AND NOT APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
    include_directories(${GTK3_INCLUDE_DIRS})
endif()

# --- Dependencia SFML ---
if(WIN32)
    # Si la tienes descargada manualmente
    include_directories(${CMAKE_SOURCE_DIR}/external/SFML-3.0/include)
    link_directories(${CMAKE_SOURCE_DIR}/external/SFML-3.0/lib)
else()
    # Linux / macOS usa la versión instalada en el sistema
    find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio Window System Network)
endif()

# --- Dependencia ENet ---
if(WIN32)
    include_directories(${CMAKE_SOURCE_DIR}/external/Enet/include)
    link_directories(${CMAKE_SOURCE_DIR}/external/Enet/lib)
    set(ENET_LIB enet)
else()
    find_library(ENET_LIB enet REQUIRED)
endif()

# --- Crear ejecutable ---
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# --- Enlazar librerías ---
target_link_libraries(${EXECUTABLE_NAME}
    PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        sfml-network
        ${ENET_LIB}
)

# --- Librerías del sistema ---
if(WIN32)
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE winmm ws2_32 opengl32)
else()
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${GTK3_LIBRARIES})
    find_package(Threads REQUIRED)
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE Threads::Threads)
endif()

# --- Mensaje bonito ---
message(STATUS "✅ Configuración lista para SFML 3.0 con C++20")

