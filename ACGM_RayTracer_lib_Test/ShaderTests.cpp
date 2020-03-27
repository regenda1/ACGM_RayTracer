#include "pch.h"

#include <ACGM_RayTracer_lib/ShaderInput.h>
#include <ACGM_RayTracer_lib/Shader.h>
#include <ACGM_RayTracer_lib/PhongShader.h>
#include <ACGM_RayTracer_lib/CheckerboardShader.h>
#include <HIRO/HIRO.h>


TEST(ShaderTests, PhongTestLight)
{
  ShaderInput input;
  input.point = glm::vec3(0.0f, 0.0f, 0.0f);
  input.normal = glm::vec3(0.0f, 0.0f, 1.0f);
  input.direction_to_eye = glm::vec3(0.0f, 0.0f, 1.0f);
  input.direction_to_light = glm::vec3(0.0f, 1.0f, 0.0f);
  input.is_point_in_shadow = false;
  input.light_intensity = 0.8f;

  acgm::PhongShader p = acgm::PhongShader(cogs::Color3f(1.0f, 0.0f, 0.0f), 2.0f, 0.2f, 0.5f, 1.0f);
  cogs::Color3f color = p.CalculateColor(input);

  EXPECT_EQ(cogs::Color3f(0.6f, 0.4f, 0.4f), color);

}

TEST(ShaderTests, PhongDirectionalTestAmbient)
{
  ShaderInput input;
  input.point = glm::vec3(0.0f, 0.0f, 0.0f);
  input.normal = glm::vec3(0.0f, 0.0f, 1.0f);
  input.direction_to_eye = glm::vec3(0.0f, 0.0f, 1.0f);
  input.direction_to_light = glm::vec3(0.0f, 1.0f, 0.0f);
  input.is_point_in_shadow = true;
  input.light_intensity = 0.8f;

  acgm::PhongShader p = acgm::PhongShader(cogs::Color3f(1.0f, 0.0f, 0.0f), 2.0f, 0.2f, 0.5f, 1.0f);
  cogs::Color3f color = p.CalculateColor(input);

  EXPECT_EQ(cogs::Color3f(0.2f, 0.0f, 0.0f), color);

}

TEST(ShaderTests, CheckerBoardShaderTestP1)
{
  ShaderInput input;
  input.point = glm::vec3(0.0f, 0.0f, 0.0f);
  input.normal = glm::vec3(0.0f, 0.0f, 1.0f);
  input.direction_to_eye = glm::vec3(0.0f, 0.0f, 1.0f);
  input.direction_to_light = glm::vec3(0.0f, 1.0f, 0.0f);
  input.is_point_in_shadow = false;
  input.light_intensity = 0.8f;

  std::shared_ptr <acgm::Shader> p1 = std::make_shared<acgm::PhongShader>(cogs::Color3f(1.0f, 0.0f, 0.0f), 2.0f, 0.2f, 0.5f, 1.0f);
  std::shared_ptr <acgm::Shader> p2 = std::make_shared<acgm::PhongShader>(cogs::Color3f(0.0f, 1.0f, 0.0f), 2.0f, 0.2f, 0.5f, 1.0f);
  acgm::CheckerBoardShader ch = acgm::CheckerBoardShader(p1, p2, 2.0f);

  cogs::Color3f color = ch.CalculateColor(input);
  EXPECT_EQ(cogs::Color3f(0.6f, 0.4f, 0.4f), color);

}

TEST(ShaderTests, CheckerBoardShaderTestP2)
{
  ShaderInput input;
  input.point = glm::vec3(3.0f, 0.0f, 0.0f);
  input.normal = glm::vec3(0.0f, 0.0f, 1.0f);
  input.direction_to_eye = glm::vec3(0.0f, 0.0f, 1.0f);
  input.direction_to_light = glm::vec3(0.0f, 1.0f, 0.0f);
  input.is_point_in_shadow = false;
  input.light_intensity = 0.8f;

  std::shared_ptr <acgm::Shader> p1 = std::make_shared<acgm::PhongShader>(cogs::Color3f(1.0f, 0.0f, 0.0f), 2.0f, 0.2f, 0.5f, 1.0f);
  std::shared_ptr <acgm::Shader> p2 = std::make_shared<acgm::PhongShader>(cogs::Color3f(0.0f, 1.0f, 0.0f), 2.0f, 0.2f, 0.5f, 1.0f);
  acgm::CheckerBoardShader ch = acgm::CheckerBoardShader(p1, p2, 2.0f);

  cogs::Color3f color = ch.CalculateColor(input);
  EXPECT_EQ(cogs::Color3f(0.4f, 0.6f, 0.4f), color);

}