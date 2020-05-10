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
#include <ACGM_RayTracer_lib/Image.h>
#include <ACGM_RayTracer_lib/IntersectionReturn.h>
#include <ACGM_RayTracer_lib/IntersectAllReturn.h>
#include <ACGM_RayTracer_lib/UnitTest.h>

namespace acgm
{
  class Scene
  {
  public:
    Scene(std::string filename, glm::vec3 enviroUp, glm::vec3 enviroSeam); //for enviromapping test
    Scene(std::shared_ptr<acgm::Camera> camera, std::shared_ptr<acgm::Light> light,
      std::vector<std::shared_ptr<Model>> models, std::string filename,
      glm::vec3 enviroUp, glm::vec3 enviroSeam, float refractive_index);
    void Raytrace(hiro::draw::RasterRenderer &renderer) const; //compute primary ray and call Trace
    cogs::Color3f DepthBasedShading(cogs::Color3f color, float hit_parameter) const;
    std::shared_ptr<acgm::Camera> GetCamera();
    cogs::Color3f Tracing(acgm::Ray r, int depth_reflection, int depth_transparency) const; //recursion for raytracing
    void SetMaxRecDepth(int ref, int trans); //set maximal recursion depth for transparency and reflection
    cogs::Color3f MapImage(acgm::Ray &r) const; //compute environment mapping
  private:
    float ambient_;
    std::vector<std::shared_ptr<Model>> models_;
    std::shared_ptr<acgm::Camera> camera_;
    std::shared_ptr<acgm::Light> light_;
    std::shared_ptr<acgm::Mesh> mesh_;
    std::shared_ptr<acgm::Image> image_;
    std::string filename_;
    glm::vec3 enviroUp_;
    glm::vec3 enviroSeam_;
    ShaderInput CreateShaderInput(IntersectionReturn &intersect, glm::vec3 point, bool is_shadow, glm::vec3 ray_dir) const;
    float refractiveIndex_;
    int maxRefDepth_;
    int maxTransDepth_;
  };


};
