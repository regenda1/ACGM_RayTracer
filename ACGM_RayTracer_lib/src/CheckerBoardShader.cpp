#include <ACGM_RayTracer_lib/CheckerBoardShader.h>

#include<math.h>

acgm::CheckerBoardShader::CheckerBoardShader(std::shared_ptr<acgm::Shader> s1, std::shared_ptr<acgm::Shader> s2, float cube_size)
{
  shader1_ = s1;
  shader2_ = s2;
  cubeSize_ = cube_size;
};

cogs::Color3f acgm::CheckerBoardShader::CalculateColor(const ShaderInput &input) const
{
  float b = 0.0001f;
  int p = std::floor(input.point.x / cubeSize_ + b) + std::floor(input.point.y / cubeSize_ + b) + std::floor(input.point.z / cubeSize_ + b);

  // decision, if used shader 1 or shader 2
  if (p % 2 == 0)
  { return shader1_->CalculateColor(input); }
  else
  { return shader2_->CalculateColor(input); }

};

float acgm::CheckerBoardShader::GetGlossiness(glm::vec3 &point) const
{
  float b = 0.0001f;
  int p = std::floor(point.x / cubeSize_ + b) + std::floor(point.y / cubeSize_ + b) + std::floor(point.z / cubeSize_ + b);

  // decision, if used shader 1 or shader 2
  if (p % 2 == 0)
  {
    return shader1_->GetGlossiness(point);
  }
  else
  {
    return shader2_->GetGlossiness(point);
  }
}

float acgm::CheckerBoardShader::GetTransparency(glm::vec3 &point) const
{
  float b = 0.0001f;
  int p = std::floor(point.x / cubeSize_ + b) + std::floor(point.y / cubeSize_ + b) + std::floor(point.z / cubeSize_ + b);

  // decision, if used shader 1 or shader 2
  if (p % 2 == 0)
  {
    return shader1_->GetTransparency(point);
  }
  else
  {
    return shader2_->GetTransparency(point);
  }
}

float acgm::CheckerBoardShader::GetRefractiveIndex(glm::vec3 &point) const
{
  float b = 0.0001f;
  int p = std::floor(point.x / cubeSize_ + b) + std::floor(point.y / cubeSize_ + b) + std::floor(point.z / cubeSize_ + b);

  // decision, if used shader 1 or shader 2
  if (p % 2 == 0)
  {
    return shader1_->GetRefractiveIndex(point);
  }
  else
  {
    return shader2_->GetRefractiveIndex(point);
  }
}



