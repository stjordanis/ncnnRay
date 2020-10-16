cmake_minimum_required (VERSION 3.15)
project(ncnnRay_wasm)

include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS "on")

if (EMSCRIPTEN)
    set(CMAKE_SYSTEM_NAME Emscripten)
    set(CMAKE_SYSTEM_VERSION 1)
    set(CMAKE_CROSSCOMPILING TRUE)
#    SET(CMAKE_C_COMPILER   emcc)
#    SET(CMAKE_CXX_COMPILER em++)
#    
    #ADD_CUSTOM_TARGET(
    #        emcc_env
    #        COMMAND cmd C:/emsdk/emsdk_env.bat
    #)
    #ADD_DEPENDENCIES(hello_world emcc_env)
    #set(CMAKE_C_COMPILER "emcc")
else()

endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo")
endif ()


#file(GLOB sourceFiles hello_world.c)
#add_executable(hello_world main.cpp)
#target_include_directories(hello_world PRIVATE ..)
#target_link_libraries(hello_world PRIVATE imtui-ncurses imtui-examples-common)


if (EMSCRIPTEN)
   add_executable(hello_world.html ncnnRay_wasm_test.c)	
   target_include_directories(hello_world.html
			PUBLIC "c:/emsdk/upstream/emscripten/system/include/emscripten/"
			"c:/emsdk/upstream/emscripten/system/include/"
			)
else()
    add_executable(hello_world ncnnRay_wasm_test.c)
	target_include_directories(hello_world
        PUBLIC "c:/emsdk/upstream/emscripten/system/include/emscripten/"
        "c:/emsdk/upstream/emscripten/system/include/"
        )
endif()