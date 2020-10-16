set PATH_OLD=%PATH%

call c:\emsdk\emsdk activate
call C:\emsdk\emsdk_env.bat

set PATH=%PATH%:%PATH_OLD%
cmake.exe -H. -Bweb -DPLATFORM=Web -G "CodeBlocks - NMake Makefiles" -DCMAKE_TOOLCHAIN_FILE=c:\emsdk\upstream\emscripten\cmake\Modules\Platform\Emscripten.cmake -DEMSCRIPTEN_ROOT=c:\emsdk\upstream\emscripten\