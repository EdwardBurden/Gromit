cmake_minimum_required(VERSION 3.10)
project(GromitPackager VERSION 1.1)

set(CMAKE_CXX_STANDARD 20)


file(GLOB GROMIT_PACKAGER "*.cpp" "*.h")
message(STATUS "Gromit Packager source files: ${GROMIT_PACKAGER}")
add_executable(${PROJECT_NAME} ${GROMIT_PACKAGER})

target_link_libraries(${PROJECT_NAME} PRIVATE Gromit)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Gromit/src)