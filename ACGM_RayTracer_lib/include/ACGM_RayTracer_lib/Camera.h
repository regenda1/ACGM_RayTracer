#pragma once

#include <glm/common.hpp>
#include <HIRO/HIRO.h>

namespace acgm
{
  class Camera
  {
  public:
    Camera();
    Camera(glm::vec3 pos, glm::vec3 upVec, glm::vec3 target, float zNear, float zFar, float fov);
    glm::vec3 GetPosition() const { return position_; };
    glm::vec3 GetUpVector() const { return upVector_; };
    glm::vec3 GetRightVector() const  { return rightVector_; };
    glm::vec3 GetLookDirection() const { return lookDirection_; };
    float GetFieldOfView() const { return fieldOfView_; };
    int GetScreenHeight() const  { return screenHeight_; };
    int GetScreenWidth() const { return screenWidth_; };
    float GetAspectRatio() const { return aspectRatio_; };
    float GetLightIntensity() const;
    float GetZNear() const;
    float GetZFar() const;
    void SetWidth(int w);
    void SetHeight(int h);
	void SetAspectRatio();
    cogs::Color3f ZNearFarColor(glm::vec3 point, cogs::Color3f color) const;
  private:
    glm::vec3 position_;
    glm::vec3 target_;
    glm::vec3 upVector_;
    glm::vec3 rightVector_;
    glm::vec3 lookDirection_;
    int screenWidth_;
    int screenHeight_;
    float fieldOfView_;
    float aspectRatio_;
    float light_intensity_;
    float farZ_;
    float nearZ_;
  };
};
