cmake_minimum_required(VERSION 3.10)
project(GromitExample VERSION 1.1)

set(CMAKE_CXX_STANDARD 20)


file(GLOB GROMIT_EXAMPLE_SOURCE "src/*.cpp" "src/*.h")
message(STATUS "Gromit Example source files: ${GROMIT_EXAMPLE_SOURCE}")
add_executable(${PROJECT_NAME} ${GROMIT_EXAMPLE_SOURCE})

target_link_libraries(${PROJECT_NAME} PRIVATE Gromit)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Gromit/src)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/pack 1"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/pack 1"
    COMMENT "Copying pack 1 folder to output directory"
)