#pragma once
#include <HIRO/HIRO.h>

namespace acgm
{
  class Light
  {
  public:
    virtual glm::vec3 GetDirectionToLight(const glm::vec3 &point) const = 0; //compute direction to light from intersection point
    virtual float GetIntensityAt(const glm::vec3 &point) const = 0; //get intensity at intersection point
    virtual float DistToLight(glm::vec3 point) const = 0; //get distance to light from intersection point
  protected:
    glm::vec3	position_;
    glm::vec3 direction_;
    float intensity_;
  };
};
