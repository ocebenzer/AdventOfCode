cmake_minimum_required(VERSION 3.5)
project(AdventOfCode)

set(CMAKE_CXX_STANDARD 23)

foreach (library "BigInt" "cpp-utils" "MultiDimensional")
    message("adding library ${library}")
    include_directories("../${library}/include")
    add_subdirectory("../${library}" ${library})
endforeach ()

# add_subdirectory(2023)
add_subdirectory(2024)
