cmake_minimum_required(VERSION 3.5)
project(AdventOfCode)

set(CMAKE_CXX_STANDARD 23)

include_directories("../BigInt/include")
include_directories("../cpp-utils/include")

add_subdirectory("../BigInt" bigint)
add_subdirectory("../cpp-utils" utilities)

# add_subdirectory(2023)
add_subdirectory(2024)
