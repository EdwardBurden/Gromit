cmake_minimum_required(VERSION 3.10)
project(Gromit LANGUAGES C CXX)

set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/spdlog")
find_package(spdlog REQUIRED)

set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw")
find_package(glfw3 3.3 REQUIRED)

set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm")
find_package(glm CONFIG REQUIRED)

set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/assimp")
find_package(assimp CONFIG REQUIRED)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE GROMIT_SOURCE "src/Gromit/*.cpp" "dependencies/glad/src/glad.c" "src/Gromit/*.h")
message(STATUS "Gromit source files: ${GROMIT_SOURCE}")
add_library(${PROJECT_NAME} SHARED ${GROMIT_SOURCE})

target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm)
target_link_libraries(${PROJECT_NAME} PUBLIC assimp::assimp)

# Public headers available to users of the engine
message(${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/Gromit)
target_include_directories(${PROJECT_NAME} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/nlohmann_json)
target_include_directories(${PROJECT_NAME} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/stb_image/include)
target_include_directories(${PROJECT_NAME} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/spdlog/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad/include)
target_include_directories(${PROJECT_NAME} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm/include)
target_include_directories(${PROJECT_NAME} PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/assimp/include)
target_precompile_headers(${PROJECT_NAME} PRIVATE "src/Gromit/pch.h")
# Define a symbol to control DLL exports (optional but recommended)
 target_compile_definitions(${PROJECT_NAME} PRIVATE GROMIT_EXPORTS)


 # Disable PCH for glad.c
set_source_files_properties("dependencies/glad/src/glad.c" PROPERTIES SKIP_PRECOMPILE_HEADERS ON)


add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    COMMENT "Copying assets folder to output directory"
)

if (WIN32)
    # Assimp’s DLL should be in the same dir as the import library
    get_target_property(ASSIMP_IMPORTED_LOCATION  assimp::assimp IMPORTED_LOCATION_RELEASE)
 get_filename_component(ASSIMP_DIR "${ASSIMP_IMPORTED_LOCATION}" DIRECTORY)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
           "${CMAKE_SOURCE_DIR}/Gromit/dependencies/assimp/bin/assimp-vc143-mtd.dll"   # <- adjust depending on your toolchain
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()