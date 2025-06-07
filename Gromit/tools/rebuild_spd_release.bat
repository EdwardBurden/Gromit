cd ../external/spdlog/build
cmake .. -DCMAKE_INSTALL_PREFIX=../../../dependencies/spdlog
cmake --build . --config Release
cmake --install . --config Release