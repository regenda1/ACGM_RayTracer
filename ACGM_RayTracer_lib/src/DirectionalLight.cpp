#include <ACGM_RayTracer_lib/DirectionalLight.h>

acgm::DirectionalLight::DirectionalLight(float intensity, glm::vec3 direction)
{
  intensity_ = intensity;
  direction_ = direction;
  position_ = glm::vec3(std::numeric_limits<float>::infinity(),
      std::numeric_limits<float>::infinity(),
      std::numeric_limits<float>::infinity());
};

glm::vec3 acgm::DirectionalLight::GetDirectionToLight(const glm::vec3 &point) const
{
  return -direction_;
};

float acgm::DirectionalLight::GetIntensityAt(const glm::vec3 &point) const
{
  return intensity_;
};

float acgm::DirectionalLight::DistToLight(glm::vec3 point) const
{
  return  glm::distance(point, position_);
};

