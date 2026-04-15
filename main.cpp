#include "Renderer.h"
#include "SceneSetup.h"
#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "Starting Engine...\n";

    int width = 600;
    int height = 400;

    // 1. INITIALIZE RENDERER FIRST (Creates OpenGL Context)
    Renderer ogl_renderer(width, height, "C++ SDL3 OpenGL Engine");

    // 2. INITIALIZE SCENE SECOND (Requires Context to build VAO/VBO/Shaders)
    Scene ogl_scene(width, height);

    // 3. START THE LOOP
    ogl_renderer.run(ogl_scene);

    std::cout << "Engine shut down successfully.\n";
    return 0;
}