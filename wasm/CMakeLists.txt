


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
