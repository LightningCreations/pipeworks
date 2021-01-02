project(fotc CXX)

add_executable(fotc src/main.cpp)

target_compile_features(fotc PUBLIC cxx_std_11)
target_link_libraries(fotc pipeworks pipeworks-sdlrenderer)
