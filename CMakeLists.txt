cmake_minimum_required(VERSION 3.21)
project(Labo_PRG2_Galton C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS="-Wall -Wconversion -Wextra –Wsign-conversion -pedantic")

add_executable(Labo_PRG2_Galton GaltonBoard.c)
