#include "../include/shader.hpp"
#include "glad/gl.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

shader::shader(const char* vertex_path, const char* fragment_path)
{
  std::string vertex_code, fragment_code;

  try 
  {
    std::ifstream v_file(vertex_path);
    std::ifstream f_file(fragment_path);
    std::stringstream v_stream, f_stream;

    v_stream << v_file.rdbuf();
    f_stream << f_file.rdbuf();

    vertex_code = v_stream.str();
    fragment_code = f_stream.str();
  }
  catch(std::ifstream::failure& error)
  {
    throw std::runtime_error("error::shader::FILE_NOT_SUCCESFULLY_READ");
  }

  const char* vertex_shader_source = vertex_code.c_str(); 
  const char* fragment_shader_source = fragment_code.c_str(); 

  uint32_t vertex_shader, fragment_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
    glCompileShader(vertex_shader);
    check_compile_errors(vertex_shader, "VERTEX");

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
    glCompileShader(fragment_shader);
    check_compile_errors(fragment_shader, "FRAGMENT");

    id = glCreateProgram();
    glAttachShader(id, vertex_shader);
    glAttachShader(id, fragment_shader);
    glLinkProgram(id); 
    check_compile_errors(id, "PROGRAM");

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

void shader::use()
{
  glUseProgram(id);
}

void shader::set_bool(const std::string &name, bool value) const 
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}
void shader::set_int(const std::string &name, int value) const 
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void shader::set_float(const std::string &name, float value) const 
{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void shader::check_compile_errors(unsigned int shader, const std::string& type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " 
                      << type << "\n" << infoLog << "\n";
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " 
                      << type << "\n" << infoLog << "\n";
        }
    }
}

uint32_t shader::get()
{
  return id;
}
