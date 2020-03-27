#include <glm/geometric.hpp>
#include <glm/gtc/epsilon.hpp>
#include <ACGM_RayTracer_lib/Sphere.h>

#include <HIRO/HIRO.h>


acgm::Sphere::Sphere(const glm::vec3 &position, float radius)
  : position_(position), radius_(radius)
{
  intersectionEpsilon_ = 0.0001f;
}

std::optional<IntersectionReturn> acgm::Sphere::intersection(const acgm::Ray &ray) const
{
  glm::vec3 oo = ray.getP() - position_;

  float A = glm::dot(ray.getD(), ray.getD());
  float B = -2.0f * glm::dot(oo, ray.getD());
  float C = glm::dot(oo, oo) - radius_ * radius_;
  float D = B * B - 4.0f * A * C;

  if (D < 0)
  {
    return std::nullopt;
  }

  float sD = glm::sqrt(D);

  float t1 = 0.5 * (B + sD) / A;
  if (t1 < intersectionEpsilon_)
  {
    t1 = INFINITY;
  }

  float t2 = 0.5 * (B - sD) / A;
  if (t2 < intersectionEpsilon_)
  {
    t2 = INFINITY;
  }

  const float t = glm::min(t1, t2);
  if (glm::isinf(t) || t < 0.0f)
  {
    return std::nullopt;
  }

  IntersectionReturn hit;
  hit.t = t;
  glm::vec3 point = ray.getP() + t * ray.getD();
  hit.normal = glm::normalize(point - position_);
  return hit;
}

const glm::vec3 &acgm::Sphere::GetPosition() const
{
  return position_;
}

float acgm::Sphere::GetRadius() const
{
  return radius_;
}

