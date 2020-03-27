#pragma once

#include <ACGM_RayTracer_lib/Light.h>

namespace acgm
{
  class SpotLight : public acgm::Light
  {
  public:
    SpotLight(float i, glm::vec3 p, float r, float attL, float attQ, glm::vec3 d, float a, float e);
    virtual glm::vec3 GetDirectionToLight(const glm::vec3 &point) const override;
    virtual float GetIntensityAt(const glm::vec3 &point) const override;
    virtual float DistToLight(glm::vec3 point) const override;
  private:
    float range_;
    float attL_;
    float attQ_;
    float cone_;
    float exponent_;
  };
};