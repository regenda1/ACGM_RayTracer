#pragma once

#include <HIRO/HIRO.h>
#include <ACGM_RayTracer_lib/IntersectionReturn.h>

namespace acgm
{
  class Ray
  {
  private:
    glm::vec3 p_; //ray position
    glm::vec3 d_; //ray direction
  public:
    Ray(glm::vec3 pArg, glm::vec3 dArg)
    {
      p_ = pArg;
      d_ = dArg;
    };
    static acgm::Ray GetReflectionRay(acgm::Ray &r, IntersectionReturn &intersection_return); //return object of reflection ray
    static std::optional<acgm::Ray> GetTransparencyRay(acgm::Ray &r, IntersectionReturn &intersection_return, float scene_index, float object_index); //return object of refraction ray
    glm::vec3 getP() const { return p_; }; //return ray position
    glm::vec3 getD() const { return d_; }; //return ray direction

  };
};
