#include <cstdint>
#include "../include/global.hpp"


const uint32_t global::scr_width = 800;
const uint32_t global::scr_height = 600;

#include "../include/framework.hpp"
#include "../include/shader.hpp"
#include "../include/mesh.hpp"
#include "../include/camera.hpp"

#include "../include/terrain.hpp"

#include "glad/gl.h"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/trigonometric.hpp>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


camera camera(glm::vec3(0.0f, 10.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, -20.0f);
void mouse_callback(GLFWwindow* window, double x_pos, double y_pos)
{
  static bool first_mouse = true;
  static float last_x = global::scr_width, last_y = global::scr_height;

  if(first_mouse)
  {
    last_x = x_pos;
    last_y = y_pos;
    first_mouse = false;
  }
  float x_offset = x_pos - last_x;
  float y_offset = y_pos - last_y;
  last_x = x_pos;
  last_y = y_pos;

  camera.process_mouse_movement(x_offset, y_offset);
}

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

    shader shader("../shader/vertex_shader.glsl", "../shader/fragment_shader.glsl");
    std::vector<float> vertices = {
        // positions          // colors
      -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // 0
       0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, // 1
       0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, // 2
      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, // 3
      -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, // 4
       0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // 5
       0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // 6
      -0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f  // 7
    };

    std::vector<unsigned int> indices = 
    { 
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        4, 0, 3,
        3, 7, 4,

        1, 5, 6,
        6, 2, 1,

        4, 5, 1,
        1, 0, 4,

        3, 2, 6,
        6, 7, 3
    };

    glfwSetInputMode(window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
    glfwSetCursorPosCallback(window.get(), mouse_callback);
    glEnable(GL_DEPTH_TEST);

    glDisable(GL_CULL_FACE);

    terrain terrain(32, 32, 32);
    terrain.generate();
    terrain.build_mesh();

    const auto& t_vertices = terrain.get_vertices();
    const auto& t_indices = terrain.get_indices();

    std::cout << "Terrain vertices: " << terrain.get_vertices().size() << "\n";
std::cout << "Terrain indices: " << terrain.get_indices().size() << "\n";

std::cerr << "First few vertices: ";
for (int i = 0; i < std::min(18, (int)terrain.get_vertices().size()); i++) {
    std::cerr << terrain.get_vertices()[i] << " ";
}
std::cerr << "\n";



    Mesh quad(t_vertices, t_indices, {3,3});

    while (!glfwWindowShouldClose(window.get())) {
        glfwPollEvents();

        glClearColor(0.6f, 0.7f, 0.7f, 1.0f); glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        glm::mat4 model = glm::mat4(1.0f); 
        glm::mat4 view = camera.get_view_matrix();
        
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);

        glUniformMatrix4fv(glGetUniformLocation(shader.get(), "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shader.get(), "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shader.get(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));


        quad.draw();

        glfwSwapBuffers(window.get());
    }

    glfwDestroyWindow(window.get());
    glfwTerminate();
    return 0;
}
