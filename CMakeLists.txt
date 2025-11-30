cmake_minimum_required(VERSION 3.20)
project(MiMotorDeJuego VERSION 0.1)

# Configura el estandar de C++ a una version moderna
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF) # Mejor practica

# Aqui es donde se anadiran las librerias Core, Renderer, Physics, etc.
# Por ahora, puedes dejar un marcador:
add_subdirectory(src/)
# add_subdirectory(src/Core)
# add_subdirectory(src/Renderer)