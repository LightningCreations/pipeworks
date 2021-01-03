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
target_compile_features(pipeworks PUBLIC cxx_std_17)
target_compile_options(pipeworks PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wpedantic -pedantic -Werror>
)

if(PIPEWORKS_BUILD_SDLRENDERER) # or any other SDL components
  if(WIN32)
    set(SDL2_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/SDL2/win32)
    message(STATUS "Set SDL2_DIR")
    message(STATUS ${SDL2_DIR})
  endif()
  find_package(SDL2 REQUIRED)
  add_library(pipeworks-sdl src/sdl/sdlmanager.cpp src/sdl/sdlmanager.hpp)
  target_include_directories(pipeworks-sdl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/sdl)
  if(DEFINED SDL2_INCLUDE_DIRS)
    target_include_directories(pipeworks-sdl PRIVATE ${SDL2_INCLUDE_DIRS})
  endif()
  if(DEFINED SDL2_LIBRARIES)
    target_link_libraries(pipeworks-sdl PRIVATE ${SDL2_LIBRARIES})
  else()
    target_link_libraries(pipeworks-sdl PRIVATE SDL2::SDL2) # Support both legacy and modern CMake config files
  endif()
endif()

if(PIPEWORKS_BUILD_SDLRENDERER)
  add_library(pipeworks-sdlrenderer src/sdlrenderer/sdlrenderer.cpp include/sdlrenderer/sdlrenderer.hpp)
  target_include_directories(pipeworks-sdlrenderer
    PUBLIC
      $<INSTALL_INTERFACE:include/sdlrenderer>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/sdlrenderer>
    PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/src/sdlrenderer
  )
  if(DEFINED SDL2_INCLUDE_DIRS)
    target_include_directories(pipeworks-sdlrenderer PRIVATE ${SDL2_INCLUDE_DIRS})
  endif()
  target_link_libraries(pipeworks-sdlrenderer
    PUBLIC
      pipeworks
    PRIVATE
      pipeworks-sdl
  )
  if(DEFINED SDL2_LIBRARIES)
    target_link_libraries(pipeworks-sdlrenderer PRIVATE ${SDL2_LIBRARIES})
  else()
    target_link_libraries(pipeworks-sdlrenderer PRIVATE SDL2::SDL2) # Support both legacy and modern CMake config files
  endif()
endif()

add_subdirectory(bindings)

if(PIPEWORKS_BUILD_DEMO)
  add_subdirectory(demo)
endif()
