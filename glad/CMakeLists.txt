set(
    Header_Files
    "include/glad/glad.h"
    "include/KHR/khrplatform.h"
)
source_group(
        TREE "${CMAKE_CURRENT_SOURCE_DIR}"
        PREFIX "Header Files"
        FILES ${Header_Files}
)

set(
    Source_Files
    "src/glad.c"
)

source_group(
        TREE "${CMAKE_CURRENT_SOURCE_DIR}"
        PREFIX "Source Files"
        FILES ${Source_Files}
)

set(
        ALL_FILES
        ${Header_Files}
        ${Source_Files}
)

set(MODULE_NAME glad)
add_library( ${MODULE_NAME} STATIC ${ALL_FILES})

find_package(OpenGL REQUIRED)

target_include_directories(
        ${MODULE_NAME} PUBLIC
        include
)

target_link_libraries(${MODULE_NAME} PUBLIC ${OPENGL_LIBRARIES})