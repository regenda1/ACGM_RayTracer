#pragma once

#include <HIRO/HIRO.h>
#include <ACGM_RayTracer_lib/Model.h>
#include <ACGM_RayTracer_lib/Mesh.h>
#include <ACGM_RayTracer_lib/Plane.h>
#include <ACGM_RayTracer_lib/Ray.h>
#include <ACGM_RayTracer_lib/Camera.h>
#include <ACGM_RayTracer_lib/IntersectionReturn.h>
#include <ACGM_RayTracer_lib/ShaderInput.h>
#include <ACGM_RayTracer_lib/Light.h>
#include <ACGM_RayTracer_lib/PointLight.h>
#include <ACGM_RayTracer_lib/SpotLight.h>
#include <ACGM_RayTracer_lib/Shader.h>
#include <ACGM_RayTracer_lib/PhongShader.h>
#include <ACGM_RayTracer_lib/CheckerBoardShader.h>

namespace acgm
{
  class UnitTest
  {
  public:
    UnitTest();
    void intersectionTest(acgm::Camera &cam);
    void getIntesityAtTest();
    void getColorTest();
  private:
    //std::shared_ptr<Model> plane_;
    //std::shared_ptr<Model> mesh_;
    std::vector<std::shared_ptr<Model>> models_;
    glm::vec3 intersectPoint_;
    glm::vec3 rayDir_;
    std::shared_ptr<Light> light_;
    std::shared_ptr<Shader> shader_;
    std::optional<IntersectionReturn> intersectionReturn_;
  };
};