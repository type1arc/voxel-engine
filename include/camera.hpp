#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "global.hpp"

class camera {
  private:
    glm::vec3 camera_pos    =   glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 camera_front  =   glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 camera_up     =   glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 camera_right; 
    glm::vec3 world_up      =   glm::vec3(0.0f, 1.0f, 0.0f);

    // orientation values
    float yaw = -90.0f; 
    float pitch = 0.0f;


  public:
    camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch)
    {
      camera_pos = pos;
      world_up = up;
      this->yaw = yaw;
      this->pitch = pitch;
      update_camera_vectors();
    }
    void process_keyboard(int key, float delta_time);
    void process_mouse_movement(float x_offset, float y_offset, bool capture_pitch = true);
    void update_camera_vectors();
    glm::mat4 get_view_matrix();
};

#endif
