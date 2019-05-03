cmake_minimum_required(VERSION 3.0)

project(ultralight-memory-test)

include(3rdparty/ultralight/ultralight.cmake)

add_executable(ultralight-memory-test-main src/main.cpp)

ultralight_add_dependency(ultralight-memory-test-main)


