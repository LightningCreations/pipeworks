cmake_minimum_required(VERSION 3.15)
project(pipeworks VERSION 0.1.0 LANGUAGES C CXX)

include(GNUInstallDirs)

find_package(Doxygen)
option(PIPEWORKS_BUILD_DOCS "Build the Doxygen documentation for Pipeworks" DOXYGEN_FOUND)

option(PIPEWORKS_BUILD_SDLRENDERER "Build the SDL2-based renderer for Pipeworks" ON)

option(PIPEWORKS_BUILD_DEMO "Build the Pipeworks demo, Fire of the Clouds" ON)
if(PIPEWORKS_BUILD_DEMO AND NOT PIPEWORKS_BUILD_SDLRENDERER)
  message(FATAL_ERROR "Building the demo requires the SDL2 renderer; please check your configuration!")
endif()

add_subdirectory(3rdparty/ring-buffer)

add_library(pipeworks
  src/engine.cpp include/engine.hpp
  src/event.cpp include/event.hpp
  src/gameobject.cpp include/gameobject.hpp
  src/imagedata.cpp
  src/renderer.cpp include/renderer.hpp
  src/scene.cpp include/scene.hpp
  src/resourcemanager.cpp include/resourcemanager.hpp

  src/objects/background.cpp include/objects/background.hpp
  src/objects/sprite.cpp include/objects/sprite.hpp

  src/stb_image.c 3rdparty/stb/stb_image.h
  src/whereami.c src/whereami.h
  src/input.cpp include/input.hpp
)
target_link_libraries(pipeworks PUBLIC ring_buffer)
target_include_directories(pipeworks
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/stb
)
target_compile_features(pipeworks PUBLIC cxx_std_20)
target_compile_options(pipeworks PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wpedantic -pedantic -Werror>
)

set_target_properties(pipeworks PROPERTIES POSITION_INDEPENDENT_CODE ON)

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
