cmake_minimum_required(VERSION 3.29)
project(AdventOfCode)

set(CMAKE_CXX_STANDARD 20)

include_directories("../BigInt/include")
include_directories("../Utils/include")

add_subdirectory("../BigInt" bigint)
add_subdirectory("../Utils" utilities)

add_subdirectory(2023)
add_subdirectory(2024)
