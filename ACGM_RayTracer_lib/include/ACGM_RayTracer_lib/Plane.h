#pragma once

#include <ACGM_RayTracer_lib/Model.h>
#include <HIRO/HIRO.h>

namespace acgm
{
  class Plane : public acgm::Model
  {
  public:
    Plane(); //for scene
    Plane(glm::vec3 qArg, glm::vec3 nArg); //for scene importer
    virtual std::optional<IntersectionReturn> intersection(const acgm::Ray &ray) const override; //compute ray plane intersection
    glm::vec3 GetQ() const { return q_; }; //get point of plane
    glm::vec3 GetN() const { return n_; }; //get normal of plane
  private:
    glm::vec3 q_; //plane point
    glm::vec3 n_; //plane normal
  };
};
