cmake_minimum_required(VERSION 3.5)
project(script)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pagezero_size 10000 -image_base 100000000")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(SOURCE_FILES script.cpp)
add_executable(script ${SOURCE_FILES})

include_directories(${PROJECT_SOURCE_DIR}/../../include)

find_library(audioToolbox AudioToolbox)
find_library(audioUnit AudioUnit)
find_library(coreAudio CoreAudio)
find_library(coreServices CoreServices)
find_library(ooLua OOLua)
find_library(luaJit LuaJIT)

target_link_libraries(script ${PROJECT_SOURCE_DIR}/../../bin/libchipaudio.a)
target_link_libraries(script ${audioUnit} ${audioToolbox} ${coreAudio} ${coreServices} ${ooLua} ${luaJit})
target_link_libraries(script -lportaudio)