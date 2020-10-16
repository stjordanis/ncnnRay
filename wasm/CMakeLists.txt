cmake_minimum_required (VERSION 3.15)
project(ncnnRay_wasm)

include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS "on")

if (EMSCRIPTEN)
    set(CMAKE_SYSTEM_NAME Emscripten)
    set(CMAKE_SYSTEM_VERSION 1)
    set(CMAKE_CROSSCOMPILING TRUE)
    if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
        set(CMAKE_C_COMPILER "emcc")
    endif ()
else()

endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo")
endif ()


#file(GLOB sourceFiles hello_world.c)
add_executable(hello_world hello_world.c)

#ADD_CUSTOM_TARGET(
#        emcc_env
#        COMMAND cmd C:/emsdk/emsdk_env.bat
#)
#ADD_DEPENDENCIES(hello_world emcc_env)

#add_executable(hello_world main.cpp)
#target_include_directories(hello_world PRIVATE ..)
#target_link_libraries(hello_world PRIVATE imtui-ncurses imtui-examples-common)
target_include_directories(hello_world
        PUBLIC "c:/emsdk/upstream/emscripten/system/include/emscripten/"
        "c:/emsdk/upstream/emscripten/system/include/"
        )
