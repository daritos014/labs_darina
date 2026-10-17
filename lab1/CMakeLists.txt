cmake_minimum_required(VERSION 3.10)
project(lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab1 main.cpp)

# Исходник содержит кириллицу в UTF-8 — говорим MSVC читать файл как UTF-8.
if(MSVC)
    target_compile_options(lab1 PRIVATE /utf-8)
endif()
