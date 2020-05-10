#pragma once

#include <ACGM_RayTracer_lib/ShaderInput.h>
#include <HIRO/HIRO.h>

namespace acgm
{
  class Shader
  {
  public:
    virtual cogs::Color3f CalculateColor(const ShaderInput &input) const = 0;
    //get parameters for reflection and transparency computation
    virtual float GetGlossiness(glm::vec3 &point) const = 0;
    virtual float GetTransparency(glm::vec3 &point) const = 0;
    virtual float GetRefractiveIndex(glm::vec3 &point) const = 0;
  };
};
