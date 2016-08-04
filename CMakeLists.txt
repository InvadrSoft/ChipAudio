cmake_minimum_required(VERSION 3.3)
project(chipaudio)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

find_path(PORTAUDIO_INCLUDE_DIR
          NAMES
          portaudio.h
          PATHS
          /portaudio/include
          /usr/include
          /usr/local/include
          /opt/local/include
          /sw/include)

find_path(OOLUA_INCLUDE_DIR
        NAMES
        oolua/oolua.h
        PATHS
        /include
        /usr/include
        /usr/local/include
        /opt/local/include
        /sw/include)

if(OOLUA_INCLUDE_DIR)
    include_directories(${OOLUA_INCLUDE_DIR})
    set(CHIPSCRIPT "chipscript.cpp")
else(OOLUA_INCLUDE_DIR)
    set(CHIPSCRIPT "")
endif(OOLUA_INCLUDE_DIR)

include_directories(${PORTAUDIO_INCLUDE_DIR})

add_subdirectory(src)