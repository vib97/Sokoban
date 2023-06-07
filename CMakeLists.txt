cmake_minimum_required(VERSION 3.5)
project(TP4_Sokoban)

option(WITH_GUI "Preparar compilacion con interfaz grafica (necesita SDL instalado)" OFF)

# IMPORTANTE: Descomentar la siguiente linea para preparar compilacion con interfaz grafica (leer el readme para las instrucciones completas)
set(WITH_GUI ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modulos/")

# Algunos flags para pasar al compilador (gnu++11 en vez de c++11 para que sea cross-plat)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=gnu++11 -ggdb3 -g")

# Dependencia de Google Test
SET(BUILD_GMOCK OFF)
SET(BUILD_GTEST ON)
add_library(gtest STATIC tests/gtest-1.8.1/gtest-all.cc)
add_library(gtest_main STATIC tests/gtest-1.8.1/gtest_main.cc)

# Leemos todos los archivos fuentes en ./src
file(GLOB SOURCE_FILES src/*.cpp src/*.h src/*.hpp)

if (WITH_GUI)
	# Leemos todos los archivos fuentes en ./gui
	file(GLOB GUI_FILES gui/*.cpp gui/*.h gui/*.hpp)

	find_package(SDL2 REQUIRED)
	find_package(SDL2_image REQUIRED)
	include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

	add_executable(sokobanGUI gui/main.cpp ${GUI_FILES} ${SOURCE_FILES})

	target_link_libraries(sokobanGUI ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
endif (WITH_GUI)

add_executable(correrTestsJuego ${SOURCE_FILES}
  tests/juego-tests.cpp
  tests/mapa-tests.cpp
  tests/nivel-tests.cpp
  tests/sokoban-tests.cpp
  tests/nuestro-juego-tests.cpp
  )

# Necesitamos asociar los archivos del framework de testing
target_link_libraries(correrTestsJuego gtest gtest_main)

# Test suites a ejecutar
add_test(correrTestsJuego juego_test)

# Target para correr Valgrind
add_custom_target(correrValgrindJuego
        valgrind --leak-check=full -v ./correrTestsJuego 2>&1
        DEPENDS correrTestsJuego)
