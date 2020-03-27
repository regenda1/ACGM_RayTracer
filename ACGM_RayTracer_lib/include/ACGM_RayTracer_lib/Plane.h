#pragma once

#include <ACGM_RayTracer_lib/Model.h>
#include <HIRO/HIRO.h>

namespace acgm
{
  class Plane : public acgm::Model
  {
  public:
    Plane();
    Plane(glm::vec3 qArg, glm::vec3 nArg);
    virtual std::optional<IntersectionReturn> intersection(const acgm::Ray &ray) const override;
    glm::vec3 GetQ() const { return q_; };
    glm::vec3 GetN() const { return n_; };
  private:
    glm::vec3 q_;
    glm::vec3 n_;
  };
};
