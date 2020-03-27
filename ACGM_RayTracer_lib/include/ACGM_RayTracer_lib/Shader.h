#pragma once

#include <ACGM_RayTracer_lib/ShaderInput.h>
#include <HIRO/HIRO.h>

namespace acgm
{
  class Shader
  {
  public:
    virtual cogs::Color3f CalculateColor(const ShaderInput &input) const = 0;
  };
};
