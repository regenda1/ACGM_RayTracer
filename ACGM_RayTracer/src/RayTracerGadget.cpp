#include "RayTracerResource.h"
#include "RayTracerGadget.h"



RayTracerGadget::RayTracerGadget(const hiro::Resource *res)
  : hiro::Gadget(res)
{
  sceneImporter_ = std::make_shared<acgm::SceneImporter>();
}

void RayTracerGadget::Initialize()
{
  hiro::Gadget::Initialize();
  style_ = std::make_shared<hiro::draw::RasterStyle>();
  style_->use_nearest_filtering = true;
  AddRenderer(GetResource<RayTracerResource>()->GetRenderer(), style_);
}

void RayTracerGadget::GenerateGui(hiro::GuiGenerator &gui)
{
  model_selector_ = gui.AddDroplist("Model")
    ->AddItemsIndexed({ "scene0.txt", "scene1.txt", "scene2.txt", "scene3.txt", "scene4.txt", "scene5.txt", "scene6.txt", "scene7.txt", "scene8.txt" })
    ->Set(0);

  maxRefDepth_ = gui.AddNumericInt("Max reflection depth");
  maxTransDepth_ = gui.AddNumericInt("Max transparency depth");

  button_ = gui.AddButton("Render");
  button_->Subscribe([this](const hiro::gui::Button * btn)
  {
    sceneImporter_->Import(model_selector_->GetText());
    acgm::RenderOptions render_options = sceneImporter_->GetRenderOptions();
    hiro::draw::PRasterRenderer renderer = GetResource<RayTracerResource>()->GetRenderer();
    renderer->SetResolution(render_options.resolution);
    std::shared_ptr<acgm::Scene> scene = sceneImporter_->GetScene();
    scene->SetMaxRecDepth(maxRefDepth_->Get(), maxTransDepth_->Get());
    scene->GetCamera()->SetWidth(render_options.resolution.x);
    scene->GetCamera()->SetHeight(render_options.resolution.y);
    scene->GetCamera()->SetAspectRatio();
    scene->Raytrace(*renderer);
  });



}


