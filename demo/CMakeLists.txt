project(fotc CXX)

add_executable(fotc
    src/blaster.cpp src/blaster.hpp
    src/main.cpp
    src/ship.cpp src/ship.hpp
    src/starfieldbackground.cpp src/starfieldbackground.hpp
)
add_custom_command(TARGET fotc POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:fotc>/assets
)

target_compile_features(fotc PUBLIC cxx_std_11)
target_link_libraries(fotc pipeworks pipeworks-sdlaudioplayer pipeworks-sdlrenderer)
