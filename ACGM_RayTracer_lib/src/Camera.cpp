#include <ACGM_RayTracer_lib/Camera.h>

acgm::Camera::Camera()
{
};

acgm::Camera::Camera(glm::vec3 pos, glm::vec3 upVec, glm::vec3 target, float zNear, float zFar, float fov)
{
  position_ = pos;
  lookDirection_ = target;
  fieldOfView_ = fov;
  screenHeight_ = 300;
  screenWidth_ = 400;
  aspectRatio_ = (float)screenWidth_ / (float)screenHeight_;
  upVector_ = upVec;
  rightVector_ = glm::normalize(glm::cross(lookDirection_, upVector_));
  light_intensity_ = 0.8f;
  nearZ_ = zNear;
  farZ_ = zFar;
};

float acgm::Camera::GetLightIntensity() const
{
  return light_intensity_;
};

bool acgm::Camera::ZNearFarColor(glm::vec3 point, cogs::Color3f color) const
{
  // z near, z far clipping
  float distance = glm::dot(lookDirection_, point - position_);
  if ((distance > nearZ_) && (distance < farZ_))
  { return false; }
  else
  {
    return true;
  }
};

float acgm::Camera::GetZNear() const
{
  return nearZ_;
};

float acgm::Camera::GetZFar() const
{
  return farZ_;
};

void acgm::Camera::SetWidth(int w)
{
  screenWidth_ = w;
}

void acgm::Camera::SetHeight(int h)
{
  screenHeight_ = h;
}

void acgm::Camera::SetAspectRatio()
{
  aspectRatio_ = (float)screenWidth_ / (float)screenHeight_;
}
