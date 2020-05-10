#pragma once
#include <ACGM_RayTracer_lib/Ray.h>
#include <HIRO/HIRO.h>
#include <math.h>


namespace acgm
{
  class Image
  {
  public:
    Image(std::string filename); //load image
    cogs::Color3f GetColorAt(const glm::vec2 &uvs) const; //compute color at u,v
  private:
    uint8_t *imgData_;
    int width_;
    int height_;
    int channels_;
  };
};
