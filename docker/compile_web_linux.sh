cmake -DCMAKE_BUILD_TYPE=Release  -G Unix Makefiles . -B web -DCMAKE_TOOLCHAIN_FILE=/emsdk_portable/emscripten/tag-1.38.40/cmake/Modules/Platform/Emscripten.cmake  && cmake --build web
