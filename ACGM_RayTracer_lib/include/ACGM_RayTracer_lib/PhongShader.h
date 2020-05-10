#pragma once
#include <ACGM_RayTracer_lib/Shader.h>

namespace acgm
{
  class PhongShader : public acgm::Shader
  {
  public:
    PhongShader();
    PhongShader(cogs::Color3f color, float shininess, float ambient, float diffuse, float specular,
      float glosiness, float transparency, float refractiv_index);
    virtual cogs::Color3f CalculateColor(const ShaderInput &input) const override;
    //get parameters for reflection and transparency computation
    virtual float GetGlossiness(glm::vec3 &point) const override;
    virtual float GetTransparency(glm::vec3 &point) const override;
    virtual float GetRefractiveIndex(glm::vec3 &point) const override;
  private:
    //parameters of shader
    float diffuzeConst_;
    float specularConst_;
    float materialShine_;
    float ambient_;
    //parameters for reflection and transparency computation
    float glosiness_;
    float transparency_;
    float refractiveIndex_;
    cogs::Color3f color_;
  };
};