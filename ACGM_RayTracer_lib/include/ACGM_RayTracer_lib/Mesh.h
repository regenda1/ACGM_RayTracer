#pragma once

#include <COGS/Mesh.h>
#include <COGS/Transform.h>

#include <ACGM_RayTracer_lib/Model.h>
#include <ACGM_RayTracer_lib/Ray.h>

namespace acgm
{
  class Mesh : public acgm::Model
  {
  public:
    Mesh();
    Mesh(glm::vec3 points[3]);
    Mesh(const std::string &fileName, glm::mat4 transform); //for scene importer
    Mesh(const cogs::Color3f &color, const std::string &fileName); // for scene
    virtual std::optional<IntersectionReturn> intersection(const acgm::Ray &ray) const override; //compute ray, mesh intersection
  private:
    cogs::Mesh mesh_;
    cogs::Transform transform_; //transformation of mesh
    glm::vec3 *meshPoints_;
    std::vector<glm::uvec3> indicesToMeshPoints_;
  };
}