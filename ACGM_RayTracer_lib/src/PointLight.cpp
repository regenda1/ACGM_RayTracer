#include <ACGM_RayTracer_lib/PointLight.h>


acgm::PointLight::PointLight(float intensity, glm::vec3 position, float range, float attL, float attQ)
{
  intensity_ = intensity;
  position_ = position;
  range_ = range;
  attL_ = attL;
  attQ_ = attQ;
};

glm::vec3 acgm::PointLight::GetDirectionToLight(const glm::vec3 &point) const
{
  return glm::normalize(position_ - point);
};

float acgm::PointLight::GetIntensityAt(const glm::vec3 &point) const
{
  float d = glm::distance(point, position_);
  float l = range_ / (range_ + d * attL_);
  float q = range_ * range_ / (range_ * range_ + d * d * attQ_);
  return l * q * intensity_;
};

float acgm::PointLight::DistToLight(glm::vec3 point) const
{
  return glm::distance(point, position_);
};