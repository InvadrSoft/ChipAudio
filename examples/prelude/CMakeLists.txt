cmake_minimum_required(VERSION 3.5)
project(prelude)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(SOURCE_FILES main.cpp)
add_executable(prelude ${SOURCE_FILES})

include_directories(${PROJECT_SOURCE_DIR}/../../include)

target_link_libraries(prelude ${PROJECT_SOURCE_DIR}/../../bin/libchipaudio.a)
target_link_libraries(prelude -lportaudio)