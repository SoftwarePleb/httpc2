cmake_minimum_required(VERSION 3.28)
project(http C)

set(CMAKE_C_STANDARD 11)

add_executable(tests tests.c
        ../src/helpers.c
        ../src/helpers.h
        ../src/requests.c
        ../src/requests.h
)
