cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
#project(music_tiles)

project(ncnnRay
        DESCRIPTION
        "ncnnRay"
        LANGUAGES
        CXX C
        )

include(FetchContent)


option(GPU_SUPPORT "Enable GPU support (Vulkan)" ON)
message("-- NCNN_VULKAN flag is ${NCNN_VULKAN}")
if (${NCNN_VULKAN})
    message("-- AUTO-ENABLING GPU_SUPPORT")
    set(GPU_SUPPORT ON)
endif()

if (GPU_SUPPORT)
    message("-- GPU support is ENABLED")
    find_package(Vulkan) # REQUIRES ncnn to be built with vulkan
    if (${VULKAN_FOUND})
        message("-- Vulkan found.")
    else()
        message("-- ERROR: AUTO-DISABLING GPU_SUPPORT, because Vulkan was not found")
        set(GPU_SUPPORT OFF)
    endif()
else()
    message("-- GPU support is DISABLED")
endif()

# shlomo
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin64)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

if( NOT CMAKE_BUILD_TYPE )
    set( CMAKE_BUILD_TYPE Release CACHE STRING
            "Choose the type of build, options are: None Debug Release RelWithDebInfo
MinSizeRel."
            FORCE )
endif()

set(CMAKE_BUILD_TYPE Release)
set(CXX_RELEASE_FLAGS = -O3 -march=native )
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "*** Have SIZEOF void * = 8, so 64-bit")
    set( IS_64_BIT 1 )
else ()
    message(STATUS "*** SIZEOF void * != 8, so not 64-bit")
    message(FATAL_ERROR "Only 64-bit i supported")
endif ()
if (MSVC)
    # Disable annoying MSVC warnings (all targets)
    add_definitions(/D "_CRT_SECURE_NO_WARNINGS")
    # Parallel build on MSVC (all targets)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# Set this to the minimal version you want to support
find_package(raylib 3.0 QUIET) # Let CMake search for a raylib-config.cmake

# You could change the QUIET above to REQUIRED and remove this if() clause
# This part downloads raylib and builds it if it's not installed on your system
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/3.0.0.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_GAMES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        # build raylib
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

set (NCNN_BUILD_EXAMPLES ON)
set (NCNN_SYSTEM_GLSLANG ON)

add_subdirectory(3rdparty/ncnn ncnn_build)
#include_directories(3rdparty/ncnn/src)

################## EXAMPLE 006 ########################
## TARGET
set(EXAMPLE_001_EXE ${PROJECT_NAME}_read_image)
#add_executable(${EXAMPLE_005_EXE} src/${EXAMPLE_005_EXE}.cpp)
add_executable(${EXAMPLE_001_EXE} src/${EXAMPLE_001_EXE}.cpp
        include/ncnnRay.hpp
        src/models/LFFD.cpp
        src/models/LFFD.h
        )
set(raylib_VERBOSE 1)
target_link_libraries(${EXAMPLE_001_EXE} raylib  ncnn)
#target_link_libraries(${PROJECT_NAME} m)
target_include_directories(${EXAMPLE_001_EXE} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/ncnn/src")
set_target_properties(${EXAMPLE_001_EXE} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES)
################## EXAMPLE 006 ########################

################# EXAMPLE 006 ########################
# TARGET
set(EXAMPLE_002_EXE ${PROJECT_NAME}_lfd)
#add_executable(${EXAMPLE_005_EXE} src/${EXAMPLE_005_EXE}.cpp)
add_executable(${EXAMPLE_002_EXE} src/${EXAMPLE_002_EXE}.cpp
        src/models/LFFD.cpp src/models/LFFD.h)
set(raylib_VERBOSE 1)
target_link_libraries(${EXAMPLE_002_EXE} raylib  ncnn)
#target_link_libraries(${PROJECT_NAME} m)
target_include_directories(${EXAMPLE_002_EXE} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/ncnn/src")
set_target_properties(${EXAMPLE_002_EXE} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES)
################# EXAMPLE 006 ########################

################# EXAMPLE 006 ########################
# TARGET
set(EXAMPLE_003_EXE ${PROJECT_NAME}_random)
#add_executable(${EXAMPLE_005_EXE} src/${EXAMPLE_005_EXE}.cpp)
add_executable(${EXAMPLE_003_EXE} src/${EXAMPLE_003_EXE}.cpp
        src/models/LFFD.cpp src/models/LFFD.h
        )
set(raylib_VERBOSE 1)
target_link_libraries(${EXAMPLE_003_EXE} raylib  ncnn)
#target_link_libraries(${PROJECT_NAME} m)
target_include_directories(${EXAMPLE_003_EXE} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/ncnn/src")
set_target_properties(${EXAMPLE_003_EXE} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES)
################# EXAMPLE 006 ########################


################# EXAMPLE 006 ########################
# TARGET
set(EXAMPLE_009_EXE ${PROJECT_NAME}_video_UI)
#add_executable(${EXAMPLE_005_EXE} src/${EXAMPLE_005_EXE}.cpp)
add_executable(${EXAMPLE_009_EXE} src/${EXAMPLE_009_EXE}.cpp
        include/ncnnRay.hpp
        include/raygui/raygui.h
        include/raygui/ricons.h
        include/pl_mpeg/pl_mpeg.h
        src/models/LFFD.cpp
        src/models/LFFD.h
        )
set(raylib_VERBOSE 1)
target_link_libraries(${EXAMPLE_009_EXE} raylib  ncnn)
#target_link_libraries(${PROJECT_NAME} m)
target_include_directories(${EXAMPLE_003_EXE} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/ncnn/src")
set_target_properties(${EXAMPLE_009_EXE} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES)
#target_compile_options(${EXAMPLE_009_EXE} PRIVATE /wd4267 /wd4244 /wd4996)
################# EXAMPLE 006 ########################

#add_executable(ncnn_ultraface src/ultra.cpp src/UltraFace.cpp)
#target_link_libraries(ncnn_ultraface ncnn)

#add_executable(ncnn_centerface src/ncnn_center.cpp src/ncnn_centerface.cpp src/ncnn_centerface.h)
#target_link_libraries(ncnn_centerface ncnn)
file(COPY "resources/parrots.png" DESTINATION ${CMAKE_SOURCE_DIR}/bin64)
file(COPY "resources/cat.png" DESTINATION ${CMAKE_SOURCE_DIR}/bin64)
file(COPY "resources/big-cat.png" DESTINATION ${CMAKE_SOURCE_DIR}/bin64)
file(COPY "resources/baboon.png" DESTINATION ${CMAKE_SOURCE_DIR}/bin64)
file(COPY "resources/faces.png" DESTINATION ${CMAKE_SOURCE_DIR}/bin64)
file(COPY "resources/windmill.png" DESTINATION ${CMAKE_SOURCE_DIR}/bin64)
file(COPY "resources/manga.png" DESTINATION ${CMAKE_SOURCE_DIR}/bin64)

# # Copy trained PTH files
file(COPY "resources/centerface.bin" DESTINATION ${CMAKE_SOURCE_DIR}/bin64)
file(COPY "resources/centerface.param" DESTINATION ${CMAKE_SOURCE_DIR}/bin64)

file(COPY "resources/symbol_10_320_20L_5scales_v2_deploy.param" DESTINATION ${CMAKE_SOURCE_DIR}/bin64)
file(COPY "resources/symbol_10_560_25L_8scales_v1_deploy.param" DESTINATION ${CMAKE_SOURCE_DIR}/bin64)

file(COPY "resources/train_10_320_20L_5scales_v2_iter_1000000.bin" DESTINATION ${CMAKE_SOURCE_DIR}/bin64)
file(COPY "resources/train_10_560_25L_8scales_v1_iter_1400000.bin" DESTINATION ${CMAKE_SOURCE_DIR}/bin64)

file(COPY "resources/GameCube.ttf" DESTINATION ${CMAKE_SOURCE_DIR}/bin64)
#file(COPY "resources/EBGaramond08-Regular.otf" DESTINATION ${CMAKE_SOURCE_DIR}/bin64)

file(COPY "resources/save.ogg" DESTINATION ${CMAKE_SOURCE_DIR}/bin64)
file(COPY "resources/click.ogg" DESTINATION ${CMAKE_SOURCE_DIR}/bin64)
file(COPY "resources/bjork-all-is-full-of-love.mpg" DESTINATION ${CMAKE_SOURCE_DIR}/bin64)

#file(COPY "resources/torch.rgs" DESTINATION ${CMAKE_SOURCE_DIR}/bin64)
file(COPY "resources/torch2.rgs" DESTINATION ${CMAKE_SOURCE_DIR}/bin64)



