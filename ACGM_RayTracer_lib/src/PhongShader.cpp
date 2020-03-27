#include <ACGM_RayTracer_lib/PhongShader.h>

acgm::PhongShader::PhongShader()
{
  diffuzeConst_ = 0.5f;
  specularConst_ = 2.0f;
  materialShine_ = 50.0f;
};

acgm::PhongShader::PhongShader(cogs::Color3f color, float shininess, float ambient, float diffuse, float specular)
{
  diffuzeConst_ = diffuse;
  specularConst_ = specular;
  materialShine_ = shininess;
  color_ = color;
  ambient_ = ambient;
};


cogs::Color3f acgm::PhongShader::CalculateColor(const ShaderInput &input) const
{
// ambient calculation
  float ambient = ambient_;
  if (input.is_point_in_shadow == false)
  {
    // diffuze computation
    float cosAlpha = (glm::dot(input.direction_to_light, input.normal) / (glm::length(input.direction_to_light) * glm::length(input.normal)));
    float diffuze = diffuzeConst_ * input.light_intensity * cosAlpha;

    // specular computation
    glm::vec3 h = glm::normalize(input.direction_to_eye + input.direction_to_light);
    float cosBeta = (glm::dot(h, input.normal) / (glm::length(h) * glm::length(input.normal)));
    float specular = specularConst_ * input.light_intensity * glm::pow(cosBeta, materialShine_);

    // color computation
    return (ambient + diffuze) * color_ + specular * cogs::Color3f(1.0f, 1.0f, 1.0f);
  }
  else
  {
    return ambient * color_;
  }
};