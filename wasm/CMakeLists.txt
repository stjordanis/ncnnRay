cmake_minimum_required (VERSION 3.15)
project(ncnnRay_wasm)

include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS "on")

if (EMSCRIPTEN)
    set(CMAKE_SYSTEM_NAME Emscripten)
    set(CMAKE_SYSTEM_VERSION 1)
    set(CMAKE_CROSSCOMPILING TRUE)
else()

endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo")
endif ()



#find_path(EMSCRIPTEN_INCLUDE_DIR emscripten/emscripten.h
#	PATHS /include
#	NO_DEFAULT_PATH
#	ONLY_CMAKE_FIND_ROOT_PATH
#	)
#
#if(NOT EMSCRIPTEN_INCLUDE_DIR)
#	message(FATAL_ERROR "emscripten.h could not be found! Is CMAKE_FIND_ROOT_PATH='${CMAKE_FIND_ROOT_PATH}' correct?")
#endif()

file(GLOB sourceFiles hello_world.c)
add_executable(hello_world ${sourceFiles})

#add_executable(hello_world main.cpp)
#target_include_directories(hello_world PRIVATE ..)
#target_link_libraries(hello_world PRIVATE imtui-ncurses imtui-examples-common)
target_include_directories(hello_world
        PUBLIC "c:/emsdk/upstream/emscripten/system/include/emscripten/"
        "c:/emsdk/upstream/emscripten/system/include/"
        )
