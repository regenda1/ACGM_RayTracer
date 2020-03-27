#include <ACGM_RayTracer_lib/Ray.h>

#include "RayTracerGadget.h"
#include "RayTracerResource.h"

#include <ACGM_RayTracer_lib/Scene.h>
#include <ACGM_RayTracer_lib/Ray.h>
#include <ACGM_RayTracer_lib/Camera.h>





RayTracerResource::RayTracerResource(const std::string &name)
  : hiro::Resource(hiro::ResourceId(name, "RayTracerResource"))
{
  raster_renderer_ = std::make_shared<hiro::draw::RasterRenderer>();

  // #TODO Set the correct resolution
  raster_renderer_->SetResolution({ 1280, 720 });
}

hiro::PGadget RayTracerResource::CreateGadget()
{
  return std::make_shared<RayTracerGadget>(this);
}

hiro::draw::PRasterRenderer RayTracerResource::GetRenderer() const
{
  return raster_renderer_;
}

