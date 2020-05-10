#pragma once

#include <ACGM_RayTracer_lib/Light.h>

namespace acgm
{
  class PointLight : public acgm::Light
  {
  public:
    PointLight(float intensity, glm::vec3 position, float range, float attL, float attQ);//init parameters
    virtual glm::vec3 GetDirectionToLight(const glm::vec3 &point) const override;
    virtual float GetIntensityAt(const glm::vec3 &point) const override;
    virtual float DistToLight(glm::vec3 point) const override;
  private:
    float range_; //range of light
    float attL_;
    float attQ_;
  };
};