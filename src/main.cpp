#include "../include/framework.hpp"
#include "../include/shader.hpp"
#include "../include/mesh.hpp"
#include <vector>

int main() {
    // Request an OpenGL 3.3 core profile context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    framework window;
    // window.show_version();

    shader shader("vertex_shader.glsl", "fragment_shader.glsl");
    std::vector<float> vertices = {
      // pos          // color
       0.5f,  0.5f,0, 1,0,0,
       0.5f, -0.5f,0, 0,1,0,
      -0.5f, -0.5f,0, 0,0,1,
      -0.5f,  0.5f,0, 1,1,0
    };

    std::vector<unsigned int> indices = {0,1,3, 1,2,3};

    // position (vec3) + color (vec3)
    Mesh quad(vertices, indices, {3,3});

    while (!glfwWindowShouldClose(window.get())) {
        glfwPollEvents();

        glClearColor(0.6f, 0.7f, 0.7f, 1.0f); glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        quad.draw();

        glfwSwapBuffers(window.get());
    }

    glfwDestroyWindow(window.get());
    glfwTerminate();
    return 0;
}
