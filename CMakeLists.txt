cmake_minimum_required(VERSION 3.27)
project(http C)

set(CMAKE_C_STANDARD 11)

add_executable(http src/main.c
        src/helpers.c
        src/helpers.h
        src/requests.c
        src/requests.h
)

