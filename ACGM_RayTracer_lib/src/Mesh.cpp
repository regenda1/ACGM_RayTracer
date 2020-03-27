#include <ACGM_RayTracer_lib\Mesh.h>

acgm::Mesh::Mesh()
{
};

// is used in tests
acgm::Mesh::Mesh(glm::vec3 points[3])
{
  indicesToMeshPoints_.push_back(glm::uvec3(0, 1, 2));
  meshPoints_ = points;
  intersectionEpsilon_ = 0.00001f;
}


// is used in scene importer
acgm::Mesh::Mesh(const std::string &fileName, glm::mat4 transform)
{
  mesh_.Import(fileName);
  indicesToMeshPoints_ = mesh_.faces->GetFaces();
  mesh_.points->Transform(transform);
  meshPoints_ = mesh_.points->GetPositions();
  intersectionEpsilon_ = 0.00001f;
}

// is used inscene
acgm::Mesh::Mesh(const cogs::Color3f &color)
{
  mesh_.Import("C:/Users/Dell/Documents/FIIT/10. semester/ACGM/3d-models/bunny.fbx");
  std::cout << "Models/Mesh: mesh has points " << mesh_.HasFaces() << std::endl;
  indicesToMeshPoints_ = mesh_.faces->GetFaces();
  transform_.SetScaling(glm::vec3(0.5f, 0.5f, 0.5f));
  transform_.SetRotation(glm::quat(glm::vec3(glm::radians(90.0f), glm::radians(0.0f), glm::radians(180.0f))));
  mesh_.points->Transform(transform_.GetMat4());
  meshPoints_ = mesh_.points->GetPositions();
  intersectionEpsilon_ = 0.00001f;
}


std::optional <IntersectionReturn> acgm::Mesh::intersection(const acgm::Ray &ray) const
{
  // init of variables
  bool is_intersection = false;
  float minT = std::numeric_limits<float>::infinity();
  cogs::Color3f color = cogs::Color3f(0.0f, 0.0f, 0.0f);
  glm::vec3 desired_normal = glm::vec3(0.0f, 0.0f, 0.0f); //normal of triangle

  // go trought triangles
  for (auto indice : indicesToMeshPoints_) 
  {
    // get normal of face
    glm::vec3 faceNormal = glm::cross((meshPoints_[indice.x] - meshPoints_[indice.y]),
        (meshPoints_[indice.x] - meshPoints_[indice.z]));
    float t = glm::dot((meshPoints_[indice.x] - ray.getP()), faceNormal) / glm::dot(ray.getD(), faceNormal); //get intersection distance
    glm::vec3 point = ray.getP() + ray.getD() * t; 

    // condition, if is inside of triangle
    glm::vec3 edge0 = meshPoints_[indice.y] - meshPoints_[indice.x];
    glm::vec3 edge1 = meshPoints_[indice.z] - meshPoints_[indice.y];
    glm::vec3 edge2 = meshPoints_[indice.x] - meshPoints_[indice.z];
    glm::vec3 C0 = point - meshPoints_[indice.x];
    glm::vec3 C1 = point - meshPoints_[indice.y];
    glm::vec3 C2 = point - meshPoints_[indice.z];

    if (glm::dot(faceNormal, glm::cross(edge0, C0)) > 0 &&
      glm::dot(faceNormal, glm::cross(edge1, C1)) > 0 &&
      glm::dot(faceNormal, glm::cross(edge2, C2)) > 0)
    {
      if (t < minT && t > intersectionEpsilon_)
      {
        minT = t;
        desired_normal = glm::normalize(faceNormal);
        is_intersection = true;
      }

    }
  }

  IntersectionReturn intersection_return;
  intersection_return.t = minT;
  intersection_return.normal = desired_normal;
  if (is_intersection == true)
  {
    return intersection_return;
  }
  else
  {
    return std::nullopt;
  }
}


