#include "pch.h"
#include <ACGM_RayTracer_lib/Scene.h>
#include <ACGM_RayTracer_lib/Ray.h>
#include <ACGM_RayTracer_lib/Image.h>
#include <HIRO/HIRO.h>

TEST(EnvironmentTests, BlackBackgroundTest)
{
  acgm::Scene scene = acgm::Scene("", glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0));
  acgm::Ray r = acgm::Ray(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0));
  cogs::Color3f color = scene.MapImage(r);
  bool is_black = false;
  if (color.r == 0 && color.b == 0 && color.g == 0)
  { is_black = true; }
  EXPECT_TRUE(is_black);
}


TEST(EnvironmentTests, ColorBackgroundTest)
{
  //we want to have yellow color from test image, because 0.5*256 is 128, and yellow color is at the
  //pixel 128,128
  acgm::Image i = acgm::Image("test1.bmp");
  cogs::Color3f color = i.GetColorAt(glm::vec2(0.5, 0.5));
  bool is_color = false;
  if (color.r == 1 && color.g == 1 && color.b == 0)
  {
    is_color = true;
  }
  EXPECT_TRUE(is_color);

}