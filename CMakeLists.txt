cmake_minimum_required(VERSION 3.15)
project(pipeworks VERSION 0.1.0 LANGUAGES CXX)

add_library(pipeworks src/engine.cpp src/engine-p.hpp include/engine.hpp)
target_include_directories(pipeworks
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_subdirectory(bindings)
