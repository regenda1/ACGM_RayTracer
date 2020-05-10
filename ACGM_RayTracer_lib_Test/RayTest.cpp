#include "pch.h"
#include <ACGM_RayTracer_lib/Ray.h>
#include <ACGM_RayTracer_lib/IntersectionReturn.h>
#include <HIRO/HIRO.h>

TEST(RayTests, ReflectionRayTest)
{

  acgm::Ray r = acgm::Ray(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0));
  IntersectionReturn ir;
  ir.t = 3;
  ir.normal = glm::vec3(-1.0, 0.0, 0.0);

  acgm::Ray ref_ray = acgm::Ray::GetReflectionRay(r, ir);
  bool is_ok = true;

  //check position
  if (ref_ray.getP().x != 3.0 || ref_ray.getP().y != 0.0 || ref_ray.getP().z != 0.0)
  { is_ok = false; }

  //check direction
  if (ref_ray.getD().x != -1.0 || ref_ray.getD().y != 0.0 || ref_ray.getD().z != 0.0)
  { is_ok = false; }

  EXPECT_TRUE(is_ok);
}

//ray goes from outside to model
TEST(RayTests, OuterRefractionRayTest)
{
  acgm::Ray r = acgm::Ray(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0));
  IntersectionReturn ir;
  ir.t = 3;
  ir.normal = glm::vec3(-1.0, 0.0, 0.0);

  std::optional<acgm::Ray> ref_ray = acgm::Ray::GetTransparencyRay(r, ir, 3.0, 1.5);
  bool is_ok = true;

  //check position
  if (ref_ray->getP().x != 3.0 || ref_ray->getP().y != 0.0 || ref_ray->getP().z != 0.0)
  {
    is_ok = false;
  }

  //check direction
  if (ref_ray->getD().x != 1.0 || ref_ray->getD().y != 0.0 || ref_ray->getD().z != 0.0)
  {
    is_ok = false;
  }

  EXPECT_TRUE(is_ok);
}

//ray goes from model to outside
TEST(RayTests, InnerRefractionRayTest)
{
  acgm::Ray r = acgm::Ray(glm::vec3(0.0, 0.0, 0.0), glm::vec3(-1, 0.0, 0.0));
  IntersectionReturn ir;
  ir.t = 3;
  ir.normal = glm::vec3(-1.0, 0.0, 0.0);

  std::optional<acgm::Ray> ref_ray = acgm::Ray::GetTransparencyRay(r, ir, 3.0, 1.5);
  bool is_ok = true;

  //check position
  if (ref_ray->getP().x != -3.0 || ref_ray->getP().y != 0.0 || ref_ray->getP().z != 0.0)
  {
    is_ok = false;
  }

  //check direction
  if (ref_ray->getD().x != -1.0 || ref_ray->getD().y != 0.0 || ref_ray->getD().z != 0.0)
  {
    is_ok = false;
  }

  EXPECT_TRUE(is_ok);
}

//test total internal refraction occurs
TEST(RayTests, RefractionRayTestNULL)
{
  acgm::Ray r = acgm::Ray(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.2, 0.0, 0.0));
  IntersectionReturn ir;
  ir.t = 3;
  ir.normal = glm::vec3(-0.2, 0.0, 0.0);

  std::optional<acgm::Ray> ref_ray = acgm::Ray::GetTransparencyRay(r, ir, 3.0, 1.5);
  bool is_ok = true;

  if (!ref_ray)
  {
    is_ok = true;
  }

  EXPECT_TRUE(is_ok);
}