set PATH_OLD=%PATH%
call c:\emsdk\emsdk activate
call C:\emsdk\emsdk_env.bat
set PATH=%PATH%:%PATH_OLD%
c:\emsdk\upstream\emscripten\emcmake cmake .
call ninja

