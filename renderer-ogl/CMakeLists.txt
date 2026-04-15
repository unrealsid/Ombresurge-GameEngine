set(
    Header_Files
    "include/Renderer.h"
    "include/SceneSetup.h"
    "include/Shader.h"
    "include/Tri.h"
)
source_group(
        TREE ${CMAKE_CURRENT_SOURCE_DIR}
        PREFIX "Header Files"
        FILES ${Header_Files}
)

set(
    Source_Files
    "source/Renderer.cpp"
    "source/SceneSetup.cpp"
    "source/Shader.cpp"
)

source_group(
        TREE ${CMAKE_CURRENT_SOURCE_DIR}
        PREFIX "Source Files"
        FILES ${Source_Files}
)

set(
        ALL_FILES
        ${Header_Files}
        ${Source_Files}
)

set(MODULE_NAME "renderer-ogl")
add_library(${MODULE_NAME} STATIC ${ALL_FILES})

target_include_directories(
    ${MODULE_NAME} PUBLIC
        include
)


target_link_libraries(${MODULE_NAME} PUBLIC ${OPENGL_LIBRARIES}
                                                    SDL3::SDL3
                                                    glad
                                                    glm)