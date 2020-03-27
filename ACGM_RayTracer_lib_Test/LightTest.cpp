#include "pch.h"

#include <ACGM_RayTracer_lib/DirectionalLight.h>
#include <ACGM_RayTracer_lib/PointLight.h>
#include <ACGM_RayTracer_lib/SpotLight.h>

#include <HIRO/HIRO.h>



TEST(LightTest, DirectionalLightTest)
{
  glm::vec3 point = glm::vec3(0.0f, 0.0f, 0.0f);
  acgm::DirectionalLight l = acgm::DirectionalLight(0.8f, glm::vec3(0.0f, -1.0f, 0.0f));
  float intensity = l.GetIntensityAt(point);
  bool equality = glm::epsilonEqual(0.8f, intensity, 0.00001f);
  EXPECT_TRUE(equality);
}

TEST(LightTest, PointLightTest)
{
  glm::vec3 point = glm::vec3(0.5f, 0.0f, 0.0f);
  acgm::PointLight l = acgm::PointLight(0.8f, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 0.5f, 0.2f);
  float intensity = l.GetIntensityAt(point);
  bool equality = glm::epsilonEqual(0.6095238f, intensity, 0.00001f);
  EXPECT_TRUE(equality);
}

TEST(LightTest, SpotLightTestTrue)
{
  glm::vec3 point = glm::vec3(0.5f, 0.0f, 0.0f);
  acgm::SpotLight l = acgm::SpotLight(0.8f, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 0.5f, 0.2f, glm::vec3(1.0f, 0.0f, 0.0f), 60.0f, 2.0f);
  float intensity = l.GetIntensityAt(point);
  bool equality = glm::epsilonEqual(0.6095238f, intensity, 0.00001f);
  EXPECT_TRUE(equality);
}

TEST(LightTest, SpotLightTestFalse)
{
  glm::vec3 point = glm::vec3(0.0f, 1.0f, 0.0f);
  acgm::SpotLight l = acgm::SpotLight(0.8f, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 0.5f, 0.2f, glm::vec3(1.0f, 0.0f, 0.0f), 60.0f, 2.0f);
  float intensity = l.GetIntensityAt(point);
  bool equality = glm::epsilonEqual(0.0f, intensity, 0.00001f);
  EXPECT_TRUE(equality);
}
