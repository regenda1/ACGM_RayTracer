#pragma once
#include <HIRO/HIRO.h>

//struct for make input for shader
struct ShaderInput
{
  glm::vec3 point;
  glm::vec3 normal;
  glm::vec3 direction_to_eye;
  glm::vec3 direction_to_light;
  bool is_point_in_shadow;
  float light_intensity;
};


