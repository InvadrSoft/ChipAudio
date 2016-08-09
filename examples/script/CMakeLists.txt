cmake_minimum_required(VERSION 3.5)
project(script)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(SOURCE_FILES script.cpp)
add_executable(script ${SOURCE_FILES})

include_directories(${PROJECT_SOURCE_DIR}/../../include)

find_library(PORTAUDIO_LIBRARY
        NAMES
        portaudio
        PATHS
        /portaudio/bin
        /usr/lib
        /usr/local/lib
        /opt/local/lib
        /sw/lib)

find_library(OOLUA_LIBRARY
             NAMES
             oolua
             OOLua
             PATHS
             /oolua/bin
             /usr/lib
             /usr/local/lib
             /opt/local/lib
             /sw/lib)

find_path(OOLUA_INCLUDE_DIR
        NAMES
        oolua/oolua.h
        PATHS
        /include
        /usr/include
        /usr/local/include
        /opt/local/include
        /sw/include)
include_directories(${OOLUA_INCLUDE_DIR})

find_path(LUA_INCLUDE_DIR
        NAMES
        lua/lua.h
        PATHS
        /include
        /usr/include
        /usr/local/include
        /opt/local/include
        /sw/include)
include_directories(${LUA_INCLUDE_DIR})

find_library(LUAJIT_LIBRARY
             NAMES
             lua53
             lua51
             luajit
             LuaJIT
             PATHS
             /lua/bin
             /LuaJIT/bin
             /usr/lib
             /usr/local/lib
             /opt/local/lib
             /sw/lib)

target_link_libraries(script ${PROJECT_SOURCE_DIR}/../../bin/libchipaudio.a ${OOLUA_LIBRARY} ${LUAJIT_LIBRARY} ${PORTAUDIO_LIBRARY})

if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pagezero_size 10000 -image_base 100000000")
    find_library(audioToolbox AudioToolbox)
    find_library(audioUnit AudioUnit)
    find_library(coreAudio CoreAudio)
    find_library(coreServices CoreServices)
    target_link_libraries(script ${audioUnit} ${audioToolbox} ${coreAudio} ${coreServices})
endif(APPLE)