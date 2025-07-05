cmake_minimum_required(VERSION 3.10)
project(GromitDevelopment VERSION 1.1)

set(CMAKE_CXX_STANDARD  20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
# Output all binaries to one location
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(Gromit)
add_subdirectory(GromitExample)