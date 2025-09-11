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

install(TARGETS Gromit
    RUNTIME DESTINATION .      # .exe, .dll on Windows
    LIBRARY DESTINATION .      # .so (Linux shared libs)
    ARCHIVE DESTINATION .      # .lib (Windows static libs)
)

install(TARGETS GromitExample
    RUNTIME DESTINATION .
)

#include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME "MyGame")
set(CPACK_PACKAGE_VENDOR "Edward Burden")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "My cool game built with CMake + CPack")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")
set(CPACK_GENERATOR "ZIP")
include(CPack)