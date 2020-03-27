#include <HIRO/HIRO.h>
//! #TODO Use cogs::Mesh to import your mesh models.
#include <COGS/Mesh.h>

#include "src/RayTracerResource.h"
#include <ACGM_RayTracer_lib/Scene.h>



int main()
{
  hiro::SetAssetDirectory("../../hiro_libs/assets/");
  hiro::SetIntermediateDirectory("./temp/");

  hiro::Initialize();

  auto resource = std::make_shared<RayTracerResource>("RayTraced Scene");
  hiro::AddResource(resource);

  // The Scene to be rendered
  // #TODO Initialize this scene with a single camera and multiple models
  //const acgm::Scene scene;

  // RayTrace the scene. Draw onto the raster renderer.
  //scene.Raytrace(*resource->GetRenderer());

  while (hiro::IsOpen())
  {
    hiro::Update();
  }

  hiro::Terminate();
  return 0;
}
