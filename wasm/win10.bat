set PATH_OLD=%PATH%
call c:\emsdk\emsdk activate
call C:\emsdk\emsdk_env.bat
set PATH=%PATH%:%PATH_OLD%
cmake -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - NMake Makefiles" -DCMAKE_TOOLCHAIN_FILE=c:/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake . && nmake