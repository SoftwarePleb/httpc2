cmake_minimum_required(VERSION 3.27)
project(http C)

set(CMAKE_C_STANDARD 11)

add_executable(http main.c
        helpers.c
        helpers.h
        requests.c
        requests.h
)

