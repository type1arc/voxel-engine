#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

static void framebuffer_size_callback(GLFWwindow* _window, int32_t _width, int32_t _height) {
  glViewport(0, 0, _width, _height);
}



class framework {
  private:
    GLFWwindow* window; 
  public:
    framework();
    ~framework();
    void show_version();
    GLFWwindow* get();
};

#endif
