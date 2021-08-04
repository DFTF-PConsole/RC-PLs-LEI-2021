cmake_minimum_required(VERSION 3.19)
project(Proj_Aux C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wextra")

add_executable(Main main.c)
add_executable(Servidor servidor.c)
add_executable(Cliente cliente.c)