cmake_minimum_required(VERSION 3.5)

project(ring_buffer LANGUAGES CXX)

set(RING_BUFFER_CXX_STANDARD "" CACHE STRING "the C++ standard version to use; if false, autodetect.")

if(RING_BUFFER_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD "${RING_BUFFER_CXX_STANDARD}")
else()
  if("cxx_std_17" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    set(CMAKE_CXX_STANDARD "17")
  elseif("cxx_std_14" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    set(CMAKE_CXX_STANDARD "14")
  else()
    message(FATAL_ERROR "compiler does not support at least C++14")
  endif()
endif()

message(STATUS "Building for C++ standard ${CMAKE_CXX_STANDARD}")

find_package(Threads REQUIRED)

add_library(ring_buffer STATIC "sources/ring_buffer.cc")
target_include_directories(ring_buffer PUBLIC $<INSTALL_INTERFACE:include> $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_link_libraries(ring_buffer PUBLIC ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(ring_buffer PROPERTIES POSITION_INDEPENDENT_CODE ON)
add_executable(ring_buffer_test EXCLUDE_FROM_ALL "tests/main.cc")
target_link_libraries(ring_buffer_test PRIVATE ring_buffer)
