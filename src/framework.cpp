#include "../include/framework.hpp"
#include <GLFW/glfw3.h>

framework::framework()
{
      if (!glfwInit())
        std::cerr << "GLFW initialization failure" << std::endl; 

      window = glfwCreateWindow(global::scr_width, global::scr_height, "voxel", nullptr, nullptr);
      if (!window)
      {
        std::cerr << "Framework: Window context creation failure.";
        glfwTerminate();
      }

      glfwMakeContextCurrent(window);
      glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

      if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
        std::cerr << "GLAD initialization failure" << std::endl;

}

framework::~framework()
{
      glfwDestroyWindow(window);
      glfwTerminate();
}

void framework::show_version()
{
      std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl; 
}

GLFWwindow* framework::get()
{
  return window;
}
