cmake_minimum_required(VERSION 3.10)
project(Gromit)

set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/spdlog")
find_package(spdlog REQUIRED)

file(GLOB_RECURSE GROMIT_SOURCE "src/Gromit/*.cpp" "src/Gromit/*.h")
message(STATUS "Gromit source files: ${GROMIT_SOURCE}")
add_library(${PROJECT_NAME} SHARED ${GROMIT_SOURCE})

target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)

target_precompile_headers(${PROJECT_NAME} PUBLIC src/Grom_pch.h)

# Public headers available to users of the engine
message(${CMAKE_CURRENT_SOURCE_DIR}/src)
#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/spdlog/include)

# Define a symbol to control DLL exports (optional but recommended)
 target_compile_definitions(${PROJECT_NAME} PRIVATE GROMIT_EXPORTS)
  target_compile_definitions(${PROJECT_NAME} PRIVATE GROMIT_PLATFORM_WINDOWS) #todo, add other platform options