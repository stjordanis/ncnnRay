set PATH_OLD=%PATH%	
call C:\emsdk\emsdk_env.bat
set PATH=%PATH%:%PATH_OLD%
cmake -DCMAKE_BUILD_TYPE=Release -DEMSCRIPTEN=ON -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=c:/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake -DCMAKE_CROSSCOMPILING_EMULATOR="C:/emsdk/node/12.18.1_64bit/bin/node.exe" . && ninja
echo "emcmake done"