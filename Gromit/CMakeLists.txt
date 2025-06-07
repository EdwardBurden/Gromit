cmake_minimum_required(VERSION 3.10)
project(Gromit)
file(GLOB GROMIT_SOURCE "src/Gromit/*.cpp" "src/Gromit/*.h")
message(STATUS "Gromit source files: ${GROMIT_SOURCE}")
add_library(${PROJECT_NAME} SHARED ${GROMIT_SOURCE})

# Public headers available to users of the engine
message(${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Define a symbol to control DLL exports (optional but recommended)
 target_compile_definitions(${PROJECT_NAME} PRIVATE GROMIT_EXPORTS)