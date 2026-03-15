#include "../include/camera.hpp"
#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>

void camera::process_mouse_movement(float x_offset, float y_offset, bool capture_pitch)
{
  static float sensitivity = 0.1f; 

  x_offset *= sensitivity;
  y_offset *= sensitivity;

  yaw += x_offset;
  pitch += y_offset;

  pitch = glm::clamp(pitch, -90.0f, 90.0f);

  update_camera_vectors();

}

void camera::update_camera_vectors()
{
  glm::vec3 front;
  front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  front.y = sin(glm::radians(pitch));
  front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  camera_front = glm::normalize(front);

  camera_right = glm::normalize(glm::cross(camera_front, camera_up));
  camera_up = glm::normalize(glm::cross(camera_right, camera_front));
}

glm::mat4 camera::get_view_matrix()
{
  return glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);
}
