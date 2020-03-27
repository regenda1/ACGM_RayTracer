#include "pch.h"

#include <ACGM_RayTracer_lib/Ray.h>
#include <ACGM_RayTracer_lib/Model.h>
#include <ACGM_RayTracer_lib/Plane.h>
#include <ACGM_RayTracer_lib/Mesh.h>
#include <ACGM_RayTracer_lib/Sphere.h>
#include <ACGM_RayTracer_lib/IntersectionReturn.h>
#include <HIRO/HIRO.h>



TEST(IntersectionTests, RayPlaneIntersectionTestTrue)
{
  acgm::Ray r = acgm::Ray(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
  acgm::Plane p = acgm::Plane(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
  std::optional<IntersectionReturn> result = p.intersection(r);
  bool isIntersect = false;
  if (result)
  {
    isIntersect = true;
  }
  EXPECT_TRUE(isIntersect);
}

TEST(IntersectionTests, RayPlaneIntersectionTestFalse)
{
  acgm::Ray r = acgm::Ray(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  acgm::Plane p = acgm::Plane(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
  std::optional<IntersectionReturn> result = p.intersection(r);
  bool isIntersect = true;
  if (result)
  {
    isIntersect = false;
  }
  EXPECT_TRUE(isIntersect);
}

TEST(IntersectionTests, RayTriangleIntersectionTestTrue)
{
  acgm::Ray r = acgm::Ray(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.5f, -1.0f));
  glm::vec3 points[3] = { glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, -1.0f) };
  acgm::Mesh m = acgm::Mesh(points);
  std::optional<IntersectionReturn> result = m.intersection(r);
  bool isIntersect = false;
  if (result)
  {
    isIntersect = true;
  }
  EXPECT_TRUE(isIntersect);
}

TEST(IntersectionTests, RayTriangleIntersectionTestFalse)
{
  acgm::Ray r = acgm::Ray(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  glm::vec3 points[3] = { glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, -1.0f) };
  acgm::Mesh m = acgm::Mesh(points);
  std::optional<IntersectionReturn> result = m.intersection(r);
  bool isIntersect = true;
  if (result)
  {
    isIntersect = false;
  }
  EXPECT_TRUE(isIntersect);
}

TEST(IntersectionTests, RaySphereIntersectionTestTrue)
{
  acgm::Ray r = acgm::Ray(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
  acgm::Sphere s = acgm::Sphere(glm::vec3(0.0f, 0.0f, -10.0f), 2.0f);
  std::optional<IntersectionReturn> result = s.intersection(r);
  bool isIntersect = false;
  if (result)
  {
    isIntersect = true;
  }
  EXPECT_TRUE(isIntersect);
}

TEST(IntersectionTests, RaySphereIntersectionTestFalse)
{
  acgm::Ray r = acgm::Ray(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  acgm::Sphere s = acgm::Sphere(glm::vec3(0.0f, 0.0f, -10.0f), 1.0f);
  std::optional<IntersectionReturn> result = s.intersection(r);
  bool isIntersect = false;
  if (result)
  {
    isIntersect = true;
  }
  EXPECT_FALSE(isIntersect);
}
