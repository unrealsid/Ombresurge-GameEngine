#include "Renderer.h"
#include "SceneSetup.h"

void Renderer::run(Scene& scene)
{
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            // Handle Window Resizing natively in SDL3
            if (event.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED) {
                width = event.window.data1;
                height = event.window.data2;
                glViewport(0, 0, width, height);

                // You might want to update scene.width / raytracer.width here
            }
        }

        scene.update();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene.draw();
        SDL_GL_SwapWindow(window);
    }
}

void Renderer::initialize_system()
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Failed to initialize SDL3\n";
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window) {
        std::cerr << "Failed to create SDL3 window\n";
        SDL_Quit();
        exit(1);
    }

    gl_context = SDL_GL_CreateContext(window);
    if (!gl_context) {
        std::cerr << "Failed to create OpenGL context\n";
        exit(1);
    }

    // Initialize GLAD to load OpenGL pointers
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        exit(1);
    }

    SDL_GL_SetSwapInterval(1); // VSync
}

void Renderer::cleanup()
{
    if (gl_context) SDL_GL_DestroyContext(gl_context);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}
