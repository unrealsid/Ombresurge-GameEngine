#include "SceneSetup.h"
#include "Shader.h"

Scene::Scene(int w, int h, int num_tris): width(w), height(h), n(num_tris)
{
    // Load the mesh instead of generating random triangles
    generate_random_triangles();
    //n = triangles.size();

    view_mode = "RASTER";

    shader = new Shader("shaders/tri.vert", "shaders/tri.frag");
    quad_shader = new Shader("shaders/quad.vert", "shaders/quad.frag");

    setup_mesh_data();

    float aspect_ratio = (float)width / (float)height;
    float exact_fov = glm::degrees(atan(1.0f / 3.0f)) * 2.0f;

    proj_mat = glm::perspective(glm::radians(exact_fov), aspect_ratio, 0.1f, 100.0f);
    view_mat = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, -6.0f));
    model_mat = glm::mat4(1.0f);
}

Scene::~Scene()
{
    delete shader;
    delete quad_shader;
}

void Scene::draw() const
{
    if (view_mode == "RASTER")
    {
        shader->use();
        shader->set_mat4("projection", proj_mat);
        shader->set_mat4("view", view_mat);
        shader->set_mat4("model", model_mat);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, n * 3);

        glBindVertexArray(bvh_vao);
        glDrawArrays(GL_LINES, 0, bvh_vertex_count);

        glBindVertexArray(0);
        glUseProgram(0);

    }
}

void Scene::setup_mesh_data()
{
    std::vector<float> vertex_data;
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    for (const auto& t : triangles) {
        glm::vec3 color(dist(rng), dist(rng), dist(rng));

        // v0
        vertex_data.push_back(t.vertex0.x); vertex_data.push_back(t.vertex0.y); vertex_data.push_back(t.vertex0.z);
        vertex_data.push_back(color.r); vertex_data.push_back(color.g); vertex_data.push_back(color.b);
        // v1
        vertex_data.push_back(t.vertex1.x); vertex_data.push_back(t.vertex1.y); vertex_data.push_back(t.vertex1.z);
        vertex_data.push_back(color.r); vertex_data.push_back(color.g); vertex_data.push_back(color.b);
        // v2
        vertex_data.push_back(t.vertex2.x); vertex_data.push_back(t.vertex2.y); vertex_data.push_back(t.vertex2.z);
        vertex_data.push_back(color.r); vertex_data.push_back(color.g); vertex_data.push_back(color.b);
    }

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_data.size() * sizeof(float), vertex_data.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Scene::generate_random_triangles()
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    for (int i = 0; i < n; i++)
    {
        glm::vec3 r0(dist(rng), dist(rng), dist(rng));
        glm::vec3 r1(dist(rng), dist(rng), dist(rng));
        glm::vec3 r2(dist(rng), dist(rng), dist(rng));

        glm::vec3 v0 = r0 * 9.0f - 5.0f;
        glm::vec3 v1 = v0 + r1;
        glm::vec3 v2 = v0 + r2;
        triangles.emplace_back(v0, v1, v2);
    }
}

void Scene::setup_screen_quad()
{
    float quad_vertices[] = {
        -1.0f,  1.0f,  0.0f, 0.0f,
        -1.0f, -1.0f,  0.0f, 1.0f,
        1.0f, -1.0f,  1.0f, 1.0f,
        -1.0f,  1.0f,  0.0f, 0.0f,
        1.0f, -1.0f,  1.0f, 1.0f,
        1.0f,  1.0f,  1.0f, 0.0f
    };

    glGenVertexArrays(1, &quad_vao);
    glGenBuffers(1, &quad_vbo);
    glBindVertexArray(quad_vao);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
}
