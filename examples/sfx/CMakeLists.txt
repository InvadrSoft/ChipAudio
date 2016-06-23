cmake_minimum_required(VERSION 3.5)
project(sfx)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(SOURCE_FILES sfx.cpp)
add_executable(sfx ${SOURCE_FILES})

include_directories(${PROJECT_SOURCE_DIR}/../../include)

find_library(audioToolbox AudioToolbox)
find_library(audioUnit AudioUnit)
find_library(coreAudio CoreAudio)
find_library(coreServices CoreServices)

target_link_libraries(sfx ${PROJECT_SOURCE_DIR}/../../bin/libchipaudio.a)
target_link_libraries(sfx ${audioUnit} ${audioToolbox} ${coreAudio} ${coreServices})
target_link_libraries(sfx -lportaudio)