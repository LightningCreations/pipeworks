
include(FindJNI)


add_library(pipeworks-jni MODULE src/Engines.cpp)

target_include_directories(pipeworks-jni PRIVATE ${JNI_INCLUDE_DIRS})

target_link_libraries(pipeworks-jni pipeworks)

