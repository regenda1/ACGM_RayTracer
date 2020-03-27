#pragma once

#include <HIRO/Gadget.h>

#include <HIRO_DRAW/renderers/RasterRenderer.h>
#include <ACGM_RayTracer_lib/SceneImporter.h>



//! Visual part of the RayTracer HIRO module.
class RayTracerGadget
  : public hiro::Gadget
{
public:
  //! Construct with a HIRO resource.
  explicit RayTracerGadget(const hiro::Resource *res);
  virtual void GenerateGui(hiro::GuiGenerator &gui) override;
  void Initialize() override;
private:
  //! Structure specifying how the raster should be rendered.
  hiro::draw::PRasterStyle style_;
  hiro::gui::Droplist *model_selector_;
  hiro::gui::Button *button_;
  std::shared_ptr<acgm::SceneImporter> sceneImporter_;
};
