#pragma once

#include <ACGM_RayTracer_lib/Shader.h>
#include <ACGM_RayTracer_lib/PhongShader.h>

namespace acgm
{
  class CheckerBoardShader : public acgm::Shader
  {
  public:
    CheckerBoardShader(std::shared_ptr<acgm::Shader> s1, std::shared_ptr<acgm::Shader> s2, float cube_size);
    virtual cogs::Color3f CalculateColor(const ShaderInput &input) const override;
  private:
    std::shared_ptr<acgm::Shader> shader1_;
    std::shared_ptr<acgm::Shader> shader2_;
    float cubeSize_;
  };
};
