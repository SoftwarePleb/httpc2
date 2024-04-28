cmake_minimum_required(VERSION 3.28)
project(http C)

set(CMAKE_C_STANDARD 11)

add_executable(http main.c
        server.c
        server.h
)
