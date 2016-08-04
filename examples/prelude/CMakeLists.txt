cmake_minimum_required(VERSION 3.5)
project(prelude)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(SOURCE_FILES prelude.cpp)
add_executable(prelude ${SOURCE_FILES})

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
target_link_libraries(prelude ${PORTAUDIO_LIBRARY})

if(APPLE)
    find_library(audioToolbox AudioToolbox)
    find_library(audioUnit AudioUnit)
    find_library(coreAudio CoreAudio)
    find_library(coreServices CoreServices)
    target_link_libraries(prelude ${audioUnit} ${audioToolbox} ${coreAudio} ${coreServices})
endif(APPLE)

target_link_libraries(prelude ${PROJECT_SOURCE_DIR}/../../bin/libchipaudio.a)