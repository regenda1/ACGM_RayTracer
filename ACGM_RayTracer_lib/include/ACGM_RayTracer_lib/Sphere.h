#pragma once
#include <ACGM_RayTracer_lib/Model.h>
#include <ACGM_RayTracer_lib/IntersectionReturn.h>



namespace acgm
{
  class Sphere : public Model
  {
  public:
    Sphere(const glm::vec3 &position, float radius);
    virtual ~Sphere() = default;
    virtual std::optional<IntersectionReturn> intersection(const acgm::Ray &ray) const override;
    const glm::vec3 &GetPosition() const;
    float GetRadius() const;
  private:
    glm::vec3 position_;
    float radius_;
  };
}
