cmake_minimum_required(VERSION 3.27)
project(SnakeG)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES main.cpp
        BoardCell.h
        Board.h
        EmptyCell.h
        SnakeCell.h
        AppleCell.h
        Board.cpp
        EmptyCell.cpp
        SnakeCell.cpp
        AppleCell.cpp
        Render.h)
add_executable(SnakeG ${SOURCE_FILES})


# Dodanie katalogu z nagłówkami Allegro do ścieżek include
include_directories("C:/USERS/48607/allegro/include")

# Dodanie katalogu z plikami biblioteki do ścieżek linkowania
link_directories("C:/USERS/48607/allegro/lib")

# Znalezienie i dodanie bibliotek Allegro
# Możesz potrzebować wylistować konkretne biblioteki, jeśli nie są one
# automatycznie znajdowane przez CMake
find_library(ALLEGRO_LIB NAMES allegro PATHS "C:/USERS/48607/allegro/lib" NO_DEFAULT_PATH)
find_library(ALLEGRO_PRIMITIVES_LIB NAMES allegro_primitives PATHS "C:/USERS/48607/allegro/lib" NO_DEFAULT_PATH)
find_library(ALLEGRO_FONT_LIB NAMES allegro_font PATHS "C:/USERS/48607/allegro/lib" NO_DEFAULT_PATH)
find_library(ALLEGRO_TTF_LIB NAMES allegro_ttf PATHS "C:/USERS/48607/allegro/lib" NO_DEFAULT_PATH)

if(NOT ALLEGRO_LIB)
    message(FATAL_ERROR "Nie znaleziono biblioteki Allegro.")
endif()

# Linkowanie bibliotek z projektem
target_link_libraries(SnakeG ${ALLEGRO_LIB} ${ALLEGRO_PRIMITIVES_LIB} ${ALLEGRO_FONT_LIB} ${ALLEGRO_TTF_LIB})

