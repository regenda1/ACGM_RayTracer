#include <ACGM_RayTracer_lib/SpotLight.h>


acgm::SpotLight::SpotLight(float i, glm::vec3 p, float r, float attL, float attQ, glm::vec3 d, float a, float e)
{
  intensity_ = i;
  position_ = p;
  range_ = r;
  attL_ = attL;
  attQ_ = attQ;
  cone_ = a;
  direction_ = d;
  exponent_ = e;
};

glm::vec3 acgm::SpotLight::GetDirectionToLight(const glm::vec3 &point) const
{
  return glm::normalize(position_ - point);
};

float acgm::SpotLight::GetIntensityAt(const glm::vec3 &point) const
{
  // intensity calculation
  float d = glm::distance(point, position_);
  float l = range_ / (range_ + d * attL_);
  float q = range_ * range_ / (range_ * range_ + d * d * attQ_);
  float intensity = l * q * intensity_;

  glm::vec3 alpha = point - position_;
  float angle = 180.0f * acos(glm::dot(direction_, alpha) / (glm::length(direction_) * glm::length(alpha))) / 3.14f;
  if (angle < cone_ )
  {
    float decay = 1.0f - glm::pow((angle / cone_), exponent_);
    return intensity * decay;
  }
  else
  { return 0.0f; }

};

float acgm::SpotLight::DistToLight(glm::vec3 point) const
{
  return glm::distance(point, position_);
};