cmake_minimum_required(VERSION 3.10)
project(GromitExample VERSION 1.1)

set(CMAKE_CXX_STANDARD 20)


file(GLOB GROMIT_EXAMPLE_SOURCE "src/*.cpp" "src/*.h")
message(STATUS "Gromit Example source files: ${GROMIT_EXAMPLE_SOURCE}")
add_executable(${PROJECT_NAME} ${GROMIT_EXAMPLE_SOURCE})

target_link_libraries(${PROJECT_NAME} PRIVATE Gromit)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Gromit/src)
#target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Gromit/dependencies/spdlog/include)