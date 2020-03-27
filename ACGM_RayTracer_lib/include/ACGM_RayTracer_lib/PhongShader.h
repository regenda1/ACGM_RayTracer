#pragma once
#include <ACGM_RayTracer_lib/Shader.h>

namespace acgm
{
  class PhongShader : public acgm::Shader
  {
  public:
    PhongShader();
    PhongShader(cogs::Color3f color, float shininess, float ambient, float diffuse, float specular);
    virtual cogs::Color3f CalculateColor(const ShaderInput &input) const override;
  private:
    float diffuzeConst_;
    float specularConst_;
    float materialShine_;
    float ambient_;
    cogs::Color3f color_;
  };
};