cmake_minimum_required(VERSION 3.7)
project(polish_notation_reverse)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c utils.c utils.h operation.c operation.h stringBuffer.c stringBuffer.h)
add_executable(polish_notation_reverse ${SOURCE_FILES})