#pragma once

#include <vector>
#include <random>
#include <glm/gtc/matrix_transform.hpp>

#include "Tri.h"
#include "glad/glad.h"


class Shader;

class Scene {
public:
    std::vector<Tri> triangles;
    int n, width, height;
    Shader* shader{};
    Shader* quad_shader{};
    std::string view_mode = "RAYTRACING";

    GLuint vao{}, vbo{};
    GLuint bvh_vao{}, bvh_vbo{};
    GLuint quad_vao{}, quad_vbo{};
    int bvh_vertex_count{};

    glm::mat4 proj_mat{};
    glm::mat4 view_mat{};
    glm::mat4 model_mat{};

    Scene(int w, int h, int num_tris = 64);

    ~Scene();

    void update() {}

    void draw() const;

private:
    void setup_mesh_data();

    void generate_random_triangles();

    void setup_screen_quad();
};
