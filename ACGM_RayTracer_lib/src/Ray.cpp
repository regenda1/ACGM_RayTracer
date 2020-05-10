#include <ACGM_RayTracer_lib/Ray.h>

//reflection ray
acgm::Ray acgm::Ray::GetReflectionRay(acgm::Ray &r, IntersectionReturn &intersection_return)
{
  glm::vec3 pos = r.getP() + intersection_return.t * r.getD();
  glm::vec3 dir = 2.0f * glm::dot(-r.getD(), intersection_return.normal) * intersection_return.normal - (-r.getD());
  return Ray(pos, dir);
}

//transparency ray
std::optional<acgm::Ray> acgm::Ray::GetTransparencyRay(acgm::Ray &r, IntersectionReturn &intersection_return,  float scene_index, float object_index)
{
  glm::vec3 pos = r.getP() + intersection_return.t * r.getD();
  glm::vec3 dir;

  float theta_1 = glm::dot(-r.getD(), intersection_return.normal);
  glm::vec3 refract_normal = intersection_return.normal;
  float eta = scene_index / object_index;
  //inside/outside test
  if (theta_1 < 0) //ray goes from inside
  {
    eta = object_index / scene_index;
    refract_normal = -refract_normal;
    theta_1 = -theta_1;
  }
  float theta_2 = 1.0f - eta * eta + eta * eta * theta_1 * theta_1;

  //check for total internal reflection
  if (theta_2 >= 0.0f)
  {
    theta_2 = glm::sqrt(theta_2);
    dir = eta * r.getD() + refract_normal * (eta * theta_1 - theta_2);
    dir = glm::normalize(dir);
    return Ray(pos, dir);
  }
  else
  {
    return std::nullopt; //when total internal reflection occurs
  }

}

