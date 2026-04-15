cmake_minimum_required(VERSION 4.1)
project(Ombresurge-opengl)

set(CMAKE_CXX_STANDARD 20)

include(cmake/Dependencies.cmake)
include(GNUInstallDirs)

add_subdirectory(glad)
add_subdirectory(renderer-ogl)

set(ENGINE_PROJECT_NAME "Ombresurge-opengl")
add_executable(${ENGINE_PROJECT_NAME} main.cpp)

find_package(OpenGL REQUIRED)

target_link_libraries(${ENGINE_PROJECT_NAME} PUBLIC ${OPENGL_LIBRARIES}
                                                    glad
                                                    renderer-ogl)