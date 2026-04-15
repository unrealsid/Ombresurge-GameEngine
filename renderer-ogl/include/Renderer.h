#pragma once

#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <iostream>
#include <string>

class Scene;

class Renderer {
public:
    int width, height;
    std::string title;
    SDL_Window* window = nullptr;
    SDL_GLContext gl_context = nullptr;

    Renderer(int w = 800, int h = 600, const std::string& t = "BVH") : width(w), height(h), title(t)
    {
        initialize_system();
    }

    ~Renderer() {
        cleanup();
    }

    void run(Scene& scene);

private:
    void initialize_system();

    void cleanup();
};
