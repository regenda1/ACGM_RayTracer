#pragma once
#include <HIRO/HIRO.h>

namespace acgm
{
  class Light
  {
  public:
    virtual glm::vec3 GetDirectionToLight(const glm::vec3 &point) const = 0;
    virtual float GetIntensityAt(const glm::vec3 &point) const = 0;
    virtual float DistToLight(glm::vec3 point) const = 0;
  protected:
    glm::vec3	position_;
    glm::vec3 direction_;
    float intensity_;
  };
};
