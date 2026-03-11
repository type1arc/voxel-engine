#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <cstdint>
#include <glad/gl.h>

class shader {
  private:
    uint32_t id;
    static void check_compile_errors(unsigned int shader, const std::string& type);
  public:

    shader(const char* vertex_path, const char* fragment_path);
    void use();

    void set_bool   (const std::string &name, bool  value) const; 
    void set_int    (const std::string &name, int   value) const; 
    void set_float  (const std::string &name, float value) const;
    uint32_t get    ();
};

#endif // !SHADER_H
