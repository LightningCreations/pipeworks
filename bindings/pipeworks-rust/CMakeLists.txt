
find_program(RUSTC rustc REQUIRED)
find_program(CARGO cargo REQUIRED)

set(CARGO_FLAGS_DEBUG --debug)
set(CARGO_FLAGS_RELEASE --release)

add_custom_target(
    NAME pipeworks-rust ALL 
        ${CMAKE_COMMAND} -E env RUSTC=${RUSTC} 
        PIPEWORKS_LIBRARY_TARGET=$<TARGET_FILE:pipeworks>
         ${CARGO} build --output
    DEPENDS pipeworks

)

