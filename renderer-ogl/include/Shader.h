#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader {
public:
    GLuint id;

    Shader(const std::string& vertex_path, const std::string& fragment_path);
    void use() const;
    void set_mat4(const std::string& name, const glm::mat4& matrix) const;
    void set_int(const std::string& name, int value) const;

private:
    std::string read_file(const std::string& filepath);
    GLuint compile_and_link(const char* v_src, const char* f_src);
    void check_compile_errors(GLuint shader_id, const std::string& type);
};