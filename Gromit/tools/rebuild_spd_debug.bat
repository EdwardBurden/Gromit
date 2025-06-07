cd ../external/spdlog/build
cmake .. -DCMAKE_INSTALL_PREFIX=../../../dependencies/spdlog
cmake --build . --config Debug
cmake --install . --config Debug