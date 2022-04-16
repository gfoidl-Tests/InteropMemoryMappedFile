cmake_minimum_required(VERSION 3.8)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

project(MemoryMappedFileTest LANGUAGES C)

add_subdirectory(ProcessA)
add_subdirectory(ProcessB)
add_subdirectory(MMFLib)
