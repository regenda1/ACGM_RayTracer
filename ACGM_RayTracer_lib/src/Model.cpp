#include <ACGM_RayTracer_lib/Model.h>

acgm::Model::Model()
{
}

std::shared_ptr<acgm::Shader> acgm::Model::GetShader() const
{
  return shader_;
};

void acgm::Model::SetShader(std::shared_ptr<acgm::Shader> shader)
{
  shader_ = shader;
};


