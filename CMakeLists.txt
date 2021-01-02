cmake_minimum_required(VERSION 3.15)
project(pipeworks VERSION 0.1.0 LANGUAGES CXX)

include(GNUInstallDirs)

option(PIPEWORKS_BUILD_DEMO "Build the Pipeworks demo, Fire of the Clouds" ON)
option(PIPEWORKS_BUILD_SDLRENDERER "Build the SDL2-based renderer for Pipeworks" ON)
if(PIPEWORKS_BUILD_DEMO AND NOT PIPEWORKS_BUILD_SDLRENDERER)
  message(FATAL_ERROR "Building the demo requires the SDL2 renderer; please check your configuration!")
endif()

add_library(pipeworks src/engine.cpp src/engine-p.hpp src/renderer.cpp src/scene.cpp include/engine.hpp include/renderer.hpp include/scene.hpp)
target_include_directories(pipeworks
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_compile_features(pipeworks PRIVATE cxx_std_17)

if(PIPEWORKS_BUILD_SDLRENDERER)
  add_library(pipeworks-sdlrenderer src/sdlrenderer/sdlrenderer.cpp include/sdlrenderer/sdlrenderer.hpp)
  target_include_directories(pipeworks
    PUBLIC
      $<INSTALL_INTERFACE:include/sdlrenderer>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/sdlrenderer>
    PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/src/sdlrenderer
  )
endif()

add_subdirectory(bindings)

if(PIPEWORKS_BUILD_DEMO)
  add_subdirectory(demo)
endif()
