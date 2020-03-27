#pragma once

#include <vector>
#include <HIRO_DRAW/renderers/RasterRenderer.h>

// #TODO: To begin with, the scene will contain one camera and a vector of models

#include <HIRO/HIRO.h>

#include <ACGM_RayTracer_lib/Plane.h>
#include <ACGM_RayTracer_lib/Ray.h>
#include <ACGM_RayTracer_lib/Camera.h>
#include <ACGM_RayTracer_lib/DirectionalLight.h>
#include <ACGM_RayTracer_lib/PointLight.h>
#include <ACGM_RayTracer_lib/SpotLight.h>
#include <ACGM_RayTracer_lib/Mesh.h>
#include <ACGM_RayTracer_lib/IntersectionReturn.h>
#include <ACGM_RayTracer_lib/IntersectAllReturn.h>
#include <ACGM_RayTracer_lib/UnitTest.h>

namespace acgm
{
  class Scene
  {
  public:
    Scene(std::shared_ptr<acgm::Camera> camera, std::shared_ptr<acgm::Light> light, std::vector<std::shared_ptr<Model>> models);
    void Raytrace(hiro::draw::RasterRenderer &renderer) const;
    cogs::Color3f DepthBasedShading(cogs::Color3f color, float hit_parameter) const;
    std::shared_ptr<acgm::Camera> GetCamera();
  private:
    float ambient_;
    std::vector<std::shared_ptr<Model>> models_;
    std::shared_ptr<acgm::Camera> camera_;
    std::shared_ptr<acgm::Light> light_;
    std::shared_ptr<acgm::Mesh> mesh_;
    ShaderInput CreateShaderInput(IntersectionReturn &intersect, glm::vec3 point, bool is_shadow, glm::vec3 ray_dir) const;
  };


};
