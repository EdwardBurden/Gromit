cmake_minimum_required(VERSION 3.10)
project(Gromit)

set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/spdlog")
find_package(spdlog REQUIRED)

set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw")
find_package(glfw3 3.3 REQUIRED)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE GROMIT_SOURCE "src/Gromit/*.cpp" "src/Gromit/*.h")
message(STATUS "Gromit source files: ${GROMIT_SOURCE}")
add_library(${PROJECT_NAME} SHARED ${GROMIT_SOURCE})

target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)

# Public headers available to users of the engine
message(${CMAKE_CURRENT_SOURCE_DIR}/src)
#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/spdlog/include)
target_precompile_headers(${PROJECT_NAME} PRIVATE "src/Gromit/pch.h")
# Define a symbol to control DLL exports (optional but recommended)
 target_compile_definitions(${PROJECT_NAME} PRIVATE GROMIT_EXPORTS)