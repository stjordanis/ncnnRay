call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
cmake.exe -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - NMake Makefiles" . -B bin64 -DCMAKE_INSTALL_PREFIX=bin64 -DEMSCRIPTEN=OFF  && cmake.exe --build bin64