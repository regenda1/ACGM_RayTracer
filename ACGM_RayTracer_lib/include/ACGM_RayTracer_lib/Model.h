#pragma once

#include <HIRO/HIRO.h>
#include <COGS/Color.h>

#include <ACGM_RayTracer_lib\IntersectionReturn.h>
#include <ACGM_RayTracer_lib/Ray.h>
#include <ACGM_RayTracer_lib/Shader.h>
#include <ACGM_RayTracer_lib/PhongShader.h>
#include <ACGM_RayTracer_lib/CheckerBoardShader.h>




namespace acgm
{
  //! Model  - abstract base class for scene models
  class Model
  {
  public:
    Model();
    virtual ~Model() = default;
    virtual std::optional<IntersectionReturn> intersection(const acgm::Ray &ray) const = 0;
    std::shared_ptr<acgm::Shader> GetShader() const;
    void SetShader(std::shared_ptr<acgm::Shader> shader);
    std::string name_;
  protected:
    float intersectionEpsilon_;
    std::shared_ptr<acgm::Shader> shader_;
  };
}
