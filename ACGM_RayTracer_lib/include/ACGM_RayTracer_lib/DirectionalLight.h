#pragma once

#include <ACGM_RayTracer_lib/Light.h>

namespace acgm
{
  class DirectionalLight : public acgm::Light
  {
  public:
    DirectionalLight(float intensity, glm::vec3 direction); //init variables
    virtual glm::vec3 GetDirectionToLight(const glm::vec3 &point) const override;
    virtual float GetIntensityAt(const glm::vec3 &point) const override;
    virtual float DistToLight(glm::vec3 point) const override; //compute distance to light
  };

};
