#pragma once
#include <HIRO/HIRO.h>

//struct for return of intersection method
struct IntersectionReturn
{
  float t; //distance of intersection
  glm::vec3 normal; //normal of surface
};