cmake_minimum_required(VERSION 3.15)
project(pipeworks VERSION 0.1.0 LANGUAGES C CXX)

include(GNUInstallDirs)

set(PIPEWORKS_USE_CXXLIB "" CACHE STRING "The C++ Standard library to use")

include(CheckCXXCompilerFlag)

if(PIPEWORKS_USE_CXXLIB)
  CHECK_CXX_COMPILER_FLAG("-stdlib=${PIPEWORKS_USE_CXXLIB}" _HAS_STDLIB)
  if(NOT _HAS_STDLIB)
    message(FATAL_ERROR "Cannot use c++lib ${PIPEWORKS_USE_CXXLIB} with ${CMAKE_CXX_COMPILER}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=${PIPEWORKS_USE_CXXLIB}")
  endif()
endif()

find_package(Doxygen)
option(PIPEWORKS_BUILD_DOCS "Build the Doxygen documentation for Pipeworks" DOXYGEN_FOUND)

option(PIPEWORKS_BUILD_DEFAULTAUDIOMIXER "Build the default audio mixing system for Pipeworks" ON)
option(PIPEWORKS_BUILD_SDLAUDIOPLAYER "Build the SDL2-based audio playback engine for Pipeworks" ON)
option(PIPEWORKS_BUILD_SDLRENDERER "Build the SDL2-based renderer for Pipeworks" ON)

option(PIPEWORKS_BUILD_DEMO "Build the Pipeworks demo, Fire of the Clouds" ON)
if(PIPEWORKS_BUILD_DEMO AND (NOT PIPEWORKS_BUILD_DEFAULTAUDIOMIXER OR NOT PIPEWORKS_BUILD_SDLAUDIOPLAYER OR NOT PIPEWORKS_BUILD_SDLRENDERER))
  message(FATAL_ERROR "Building the demo requires the SDL2 tools and the default audio mixer; please check your configuration!")
endif()


CHECK_CXX_COMPILER_FLAG("-march=native" MARCH_NATIVE_SUPPORTED)

option(PIPEWORKS_MARCH_NATIVE "Build the pipeworks libraries with the -march=native flag" MARCH_NATIVE_SUPPORTED)
if(PIPEWORKS_MARCH_NATIVE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
endif()

add_subdirectory(3rdparty/ring-buffer)

if(NOT WIN32)
  find_package(TBB REQUIRED)
  set(PIPEWORKS_LINK_LIBTBB TBB::tbb)
endif()

add_library(pipeworks
  src/audiomixer.cpp include/audiomixer.hpp
  src/audioplayer.cpp include/audioplayer.hpp
  src/engine.cpp include/engine.hpp
  src/event.cpp include/event.hpp
  src/gameobject.cpp include/gameobject.hpp
  src/imagedata.cpp
  src/renderer.cpp include/renderer.hpp
  src/scene.cpp include/scene.hpp
  src/resourcemanager.cpp include/resourcemanager.hpp

  src/objects/background.cpp include/objects/background.hpp
  src/objects/bgm.cpp include/objects/bgm.hpp
  src/objects/emitter.cpp include/objects/emitter.hpp
  src/objects/soundeffect.cpp include/objects/soundeffect.hpp
  src/objects/sprite.cpp include/objects/sprite.hpp

  src/dr_flac.c 3rdparty/dr_libs/dr_flac.h
  src/stb_image.c 3rdparty/stb/stb_image.h
  src/whereami.c src/whereami.h
  src/input.cpp include/input.hpp

  src/collision.cpp include/collision.hpp
)
target_link_libraries(pipeworks PUBLIC ring_buffer ${PIPEWORKS_LINK_LIBTBB})
target_include_directories(pipeworks
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/dr_libs
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/stb
)
target_compile_features(pipeworks PUBLIC cxx_std_20)
target_compile_options(pipeworks PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wpedantic -pedantic -Werror>
)

set_target_properties(pipeworks PROPERTIES POSITION_INDEPENDENT_CODE ON)

if(PIPEWORKS_BUILD_DEFAULTAUDIOMIXER)
  add_library(pipeworks-defaultaudiomixer src/defaultaudiomixer/defaultaudiomixer.cpp include/defaultaudiomixer/defaultaudiomixer.hpp)
  target_include_directories(pipeworks-defaultaudiomixer
    PUBLIC
      $<INSTALL_INTERFACE:include/defaultaudiomixer>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/defaultaudiomixer>
    PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/src/defaultaudiomixer
  )

  set_target_properties(pipeworks-defaultaudiomixer PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()

if(PIPEWORKS_BUILD_SDLRENDERER OR PIPEWORKS_BUILD_SDLAUDIOPLAYER) # or any other SDL components
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

if(PIPEWORKS_BUILD_SDLAUDIOPLAYER)
  add_library(pipeworks-sdlaudioplayer src/sdlaudioplayer/sdlaudioplayer.cpp include/sdlaudioplayer/sdlaudioplayer.hpp)
  target_include_directories(pipeworks-sdlaudioplayer
    PUBLIC
      $<INSTALL_INTERFACE:include/sdlaudioplayer>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/sdlaudioplayer>
    PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/src/sdlaudioplayer
  )

  set_target_properties(pipeworks-sdlaudioplayer PROPERTIES POSITION_INDEPENDENT_CODE ON)
  if(DEFINED SDL2_INCLUDE_DIRS)
    target_include_directories(pipeworks-sdlaudioplayer PUBLIC ${SDL2_INCLUDE_DIRS})
  endif()
  target_link_libraries(pipeworks-sdlaudioplayer
    PUBLIC
      pipeworks
    PRIVATE
      pipeworks-sdl
  )
  if(DEFINED SDL2_LIBRARIES)
    target_link_libraries(pipeworks-sdlaudioplayer PUBLIC ${SDL2_LIBRARIES} "-pthread") # Because SDL2 needs pthread and doesn't declare it?
  else()
    target_link_libraries(pipeworks-sdlaudioplayer PUBLIC SDL2::SDL2) # Support both legacy and modern CMake config files
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

  set_target_properties(pipeworks-sdlrenderer PROPERTIES POSITION_INDEPENDENT_CODE ON)
  if(DEFINED SDL2_INCLUDE_DIRS)
    target_include_directories(pipeworks-sdlrenderer PUBLIC ${SDL2_INCLUDE_DIRS})
  endif()
  target_link_libraries(pipeworks-sdlrenderer
    PUBLIC
      pipeworks
    PRIVATE
      pipeworks-sdl
  )
  if(DEFINED SDL2_LIBRARIES)
    target_link_libraries(pipeworks-sdlrenderer PUBLIC ${SDL2_LIBRARIES} "-pthread") # Because SDL2 needs pthread and doesn't declare it?
  else()
    target_link_libraries(pipeworks-sdlrenderer PUBLIC SDL2::SDL2) # Support both legacy and modern CMake config files
  endif()
endif()

if(PIPEWORKS_BUILD_DOCS)
  find_package(Doxygen REQUIRED)
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    @ONLY
  )

  add_custom_target(doc ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running Doxygen"
    VERBATIM
  )

  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/ TYPE DOC)
endif()

add_subdirectory(bindings)

if(PIPEWORKS_BUILD_DEMO)
  add_subdirectory(demo)
endif()
