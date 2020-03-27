#include <ACGM_RayTracer_lib/Scene.h>
#include <ACGM_RayTracer_lib/ShaderInput.h>
#include <ACGM_RayTracer_lib/IntersectionReturn.h>
#include <ACGM_RayTracer_lib/Ray.h>

#include <HIRO/HIRO.h>
#include <limits>

acgm::Scene::Scene(std::shared_ptr<acgm::Camera> camera, std::shared_ptr<acgm::Light> light, std::vector<std::shared_ptr<Model>> models)
{
  camera_ = camera;
  light_ = light;
  models_ = models;
  ambient_ = 0.2f;
};

void acgm::Scene::Raytrace(hiro::draw::RasterRenderer &renderer) const
{
  glm::vec3 cameraPos = camera_->GetPosition();

  float pi = 3.14f;
  float d180 = 180.0f;
  float startPoint = (-1.0f) * tan(pi * (camera_->GetFieldOfView() / 2.0f) / d180); //the angle, where ray started
  // init of ray direction. They started at startPoint, but dirX is extended by aspect ratio (we want more or less pixels)
  float dirY = startPoint;
  float dirX = startPoint * camera_->GetAspectRatio();
  // step which ray takes in x and y direction
  float stepY = 2.0f * tan(pi * (camera_->GetFieldOfView() / 2.0f) / d180) / (float)camera_->GetScreenHeight();
  float stepX = 2.0f * tan(pi * (camera_->GetFieldOfView() / 2.0f) / d180) * camera_->GetAspectRatio() / (float)camera_->GetScreenWidth();
  dirY += stepY / 2.0f;
  dirX += stepX / 2.0f;

  #pragma omp parallel for
  for (int i = 0; i < camera_->GetScreenHeight(); i++)
  {
    for (int j = 0; j < camera_->GetScreenWidth(); j++)
    {
      // the ray is created
      glm::vec3 dir = glm::normalize(camera_->GetLookDirection() + (dirX + j * stepX) * camera_->GetRightVector() + (dirY + i * stepY) * camera_->GetUpVector());
      acgm::Ray r = acgm::Ray(camera_->GetPosition(), dir);

      // intersection
      std::optional<IntersectionReturn> intersection_return;
      cogs::Color3f color = cogs::Color3f(0.0f, 0.0f, 0.0f);
      glm::vec3 normal;
      std::shared_ptr<acgm::Model> m;
      float minT = std::numeric_limits<float>::infinity();
      bool is_intersection = false;
      for (auto &model : models_)
      {
        intersection_return = model->intersection(r);
        if (intersection_return && intersection_return->t < minT)
        {
          minT = intersection_return->t;
          normal = intersection_return->normal;
          m = model;
          is_intersection = true;
        }
      }

      if (is_intersection)
      {
        intersection_return->t = minT;
        intersection_return->normal = normal;
      }

      if (is_intersection)
      {
        // the ray for lighting is created
        acgm::Ray light_ray = acgm::Ray(r.getP() + minT * r.getD(), light_->GetDirectionToLight(r.getP() + minT * r.getD()));

        // intersection for lighting
        std::optional<IntersectionReturn> light_return;
        float min_t_light = std::numeric_limits<float>::infinity();
        bool is_light_intersect = false;
        for (auto &model : models_)
        {
          light_return = model->intersection(light_ray);
          if (light_return && light_return->t < min_t_light)
          {
            min_t_light = light_return->t;
            is_light_intersect = true;
          }
        }

        // here is decided, if shadow exists
        float light_or_shadow;
        bool is_shadow = false;
        if(is_light_intersect)
        {
          float dist_to_light = light_->DistToLight(r.getP() + minT * r.getD());

          if(min_t_light < dist_to_light)
          {
            light_or_shadow = ambient_;
            is_shadow = true;
          }
          else
          {
            light_or_shadow = ambient_ + (1 - ambient_) * light_->GetIntensityAt(r.getP() + minT * r.getD());
          }
        }
        else
        {
          light_or_shadow = ambient_ + (1 - ambient_) * light_->GetIntensityAt(r.getP() + minT * r.getD());
        }

        // color computation in shader
        ShaderInput input = CreateShaderInput(*intersection_return, (r.getP() + minT * r.getD()), is_shadow, dir);
        color = m->GetShader()->CalculateColor(input);

        //color = DepthBasedShading(color, minT);
        color = camera_->ZNearFarColor(r.getP() + minT * r.getD(), color);
      }
      renderer.SetPixel(j, i, color);
    }
  }
}

cogs::Color3f acgm::Scene::DepthBasedShading(cogs::Color3f color, float hit_parameter) const
{
  float near = camera_->GetZNear();
  float far = camera_->GetZFar();
  hit_parameter = (hit_parameter - near) / (far - near);
  float intensity = camera_->GetLightIntensity() / hit_parameter;
  return color * intensity;
};


// setup of input for shader
ShaderInput acgm::Scene::CreateShaderInput(IntersectionReturn &intersect, glm::vec3 point, bool is_shadow, glm::vec3 ray_dir) const
{
  ShaderInput input;
  input.direction_to_eye = -ray_dir;
  input.direction_to_light = light_->GetDirectionToLight(point);
  input.light_intensity = light_->GetIntensityAt(point);
  input.normal = intersect.normal;
  input.is_point_in_shadow = is_shadow;
  input.point = point;
  return input;
};

std::shared_ptr<acgm::Camera> acgm::Scene::GetCamera()
{
  return camera_;
}
