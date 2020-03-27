#pragma once
#include <HIRO/HIRO.h>
#include <ACGM_RayTracer_lib/IntersectionReturn.h>
#include <ACGM_RayTracer_lib/Model.h>

struct IntersectAllReturn
{
  IntersectionReturn intersect;
  std::shared_ptr<acgm::Model> model;
};
