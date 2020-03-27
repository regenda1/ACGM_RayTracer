#include <ACGM_RayTracer_lib/Plane.h>
#include <ACGM_RayTracer_lib/Model.h>


acgm::Plane::Plane()
{
};

acgm::Plane::Plane(glm::vec3 qArg, glm::vec3 nArg)
{
  q_ = qArg;
  n_ = nArg;
  intersectionEpsilon_ = 0.00001f;
};

std::optional<IntersectionReturn> acgm::Plane::intersection(const acgm::Ray &ray) const
{
  // init of variables
  bool is_intersection = false;
  cogs::Color3f color = cogs::Color3f(0.0f, 0.0f, 0.0f); 
  // get distance of intersection
  float t = glm::dot((q_ - ray.getP()), n_) / glm::dot(ray.getD(), n_); 

  if (t > intersectionEpsilon_) 
  {
    is_intersection = true;
  }

  IntersectionReturn intersection_return;
  intersection_return.t = t;
  intersection_return.normal = n_;

  if (is_intersection == true)
  { return intersection_return; }
  else
  { return std::nullopt; }
}


