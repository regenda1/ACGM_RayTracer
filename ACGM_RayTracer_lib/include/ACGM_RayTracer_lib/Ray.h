#pragma once

#include <HIRO/HIRO.h>

namespace acgm
{
  class Ray
  {
  private:
    glm::vec3 p_;
    glm::vec3 d_;
  public:
    Ray(glm::vec3 pArg, glm::vec3 dArg)
    {
      p_ = pArg;
      d_ = dArg;
    };
    glm::vec3 getP() const { return p_; };
    glm::vec3 getD() const { return d_; };
  };
};
