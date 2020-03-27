#include <ACGM_RayTracer_lib/UnitTest.h>

acgm::UnitTest::UnitTest()
{
  //mesh_ = new Mesh()->createMeshForTest;
  //zadna tyrkysova
  //plane_ = std::make_shared<acgm::Plane>(glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), cogs::Color3f(0.0f, 1.0f, 1.0f));
// models_.push_back(std::make_shared<acgm::Plane>(glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f), cogs::Color3f(0.0f, 1.0f, 1.0f))); //zadok
  models_.push_back(std::make_shared<acgm::Mesh>());
}

void acgm::UnitTest::intersectionTest(acgm::Camera &cam)
{
  /*
    //spravi sa luc
    rayDir_ = glm::vec3(0.0f, 0.25f, 0.0f);
    acgm::Ray r = acgm::Ray(cam.GetPosition(), rayDir_);

    //std::optional<IntersectionReturn> intersection_return;
    cogs::Color3f color = cogs::Color3f(0.0f, 0.0f, 0.0f);
    glm::vec3 normal;
    std::shared_ptr<acgm::Model> m;
    float minT = std::numeric_limits<float>::infinity();
    bool is_intersection = false;
    intersectionReturn_ = models_[0]->intersection(r);
    std::cout << "UnitTest.cpp/intersectionTest: min t je " << intersectionReturn_->t << std::endl;
  */

  /*
    for (auto &model : models_)
    {
    intersectionReturn_ = model->intersection(r);
    if (intersectionReturn_ && intersectionReturn_->t < minT)
    {
  	  minT = intersectionReturn_->t;
  	  color = intersectionReturn_->color;
  	  normal = intersectionReturn_->normal;
  	  m = model;
  	  is_intersection = true;
    }
    }
  */
// intersectPoint_ = r.getP() + r.getD() * minT;
};

void acgm::UnitTest::getIntesityAtTest()
{
  /*
    //std::shared_ptr<Light> light;
    light_ = std::make_shared<acgm::PointLight>();
    float intensity = light_->GetIntensityAt(intersectPoint_);
    std::cout << "UnitTest.cpp / getIntesityAtTest: pointLight intensity is: " << intensity << std::endl;

    light_ = std::make_shared<acgm::SpotLight>();
    intensity = light_->GetIntensityAt(intersectPoint_);
    std::cout << "UnitTest.cpp / getIntesityAtTest: spotLight intensity is: " << intensity << std::endl;
  */
}

void acgm::UnitTest::getColorTest()
{
  /*
    ShaderInput input;
    //input.ambient = 0.2f;
    //input.color = intersectionReturn_->color;
    input.direction_to_eye = -rayDir_;
    input.direction_to_light = light_->GetDirectionToLight(intersectPoint_);
    input.light_intensity = light_->GetIntensityAt(intersectPoint_);
    input.normal = intersectionReturn_->normal;
    input.is_point_in_shadow = false;
    input.point = intersectPoint_;

    shader_ = std::make_shared<acgm::PhongShader>();
    cogs::Color3f color = shader_->CalculateColor(input);
    std::cout << "UnitTest.cpp / getColorTest: phongShader color is: " << color.r << color.g << color.b << std::endl;

    shader_ = std::make_shared<acgm::CheckerBoardShader>();
    color = shader_->CalculateColor(input);
    std::cout << "UnitTest.cpp / getColorTest: checkerBoardShader color is: " << color.r << color.g << color.b << std::endl;
  */
}