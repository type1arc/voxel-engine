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

    // orientation values
    float yaw = -90.0f; 
    float pitch = 0.0f;
    float last_x = global::scr_width / 2.0f;
    float last_y = global::scr_height / 2.0f; 
    bool first_mouse = true;


  public:
    camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch)
    {
      camera_pos = pos;
      camera_up = up;
      yaw = yaw;
      pitch = pitch;
      update_camera_vectors();
    }
    void process_mouse_movement(float x_offset, float y_offset, bool capture_pitch = true);
    void update_camera_vectors();
    glm::mat4 get_view_matrix();
};

#endif // CAMERA_HPP
