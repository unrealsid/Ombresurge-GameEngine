#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>
#include "glad/glad.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& vertex_path, const std::string& fragment_path) {
    std::string vertex_src = read_file(vertex_path);
    std::string fragment_src = read_file(fragment_path);
    id = compile_and_link(vertex_src.c_str(), fragment_src.c_str());
}

void Shader::use() const {
    glUseProgram(id);
}

void Shader::set_mat4(const std::string& name, const glm::mat4& matrix) const {
    GLint location = glGetUniformLocation(id, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::set_int(const std::string& name, int value) const {
    GLint location = glGetUniformLocation(id, name.c_str());
    glUniform1i(location, value);
}

std::string Shader::read_file(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Shader file '" << filepath << "' not found.\n";
        exit(1);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint Shader::compile_and_link(const char* v_src, const char* f_src) {
    GLuint v_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v_shader, 1, &v_src, nullptr);
    glCompileShader(v_shader);
    check_compile_errors(v_shader, "VERTEX");

    GLuint f_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(f_shader, 1, &f_src, nullptr);
    glCompileShader(f_shader);
    check_compile_errors(f_shader, "FRAGMENT");

    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, v_shader);
    glAttachShader(program_id, f_shader);
    glLinkProgram(program_id);
    check_compile_errors(program_id, "PROGRAM");

    glDeleteShader(v_shader);
    glDeleteShader(f_shader);

    return program_id;
}

void Shader::check_compile_errors(GLuint shader_id, const std::string& type) {
    GLint success;
    GLchar info_log[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader_id, 1024, nullptr, info_log);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << info_log << "\n";
            exit(1);
        }
    } else {
        glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader_id, 1024, nullptr, info_log);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << info_log << "\n";
            exit(1);
        }
    }
}