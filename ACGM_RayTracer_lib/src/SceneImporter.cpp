#include <ACGM_RayTracer_lib/SceneImporter.h>
#include <Utils/Dialogs.h>

#include <ACGM_RayTracer_lib/Plane.h>
#include <ACGM_RayTracer_lib/Sphere.h>
#include <ACGM_RayTracer_lib/Mesh.h>
#include <ACGM_RayTracer_lib/Shader.h>
#include <ACGM_RayTracer_lib/Camera.h>
#include <ACGM_RayTracer_lib/Image.h>



const int acgm::SceneImporter::MODELTYPE_PLANE = 20;
const int acgm::SceneImporter::MODELTYPE_SPHERE = 21;
const int acgm::SceneImporter::MODELTYPE_MESH = 22;
const int acgm::SceneImporter::LIGHTTYPE_SUN = 10;
const int acgm::SceneImporter::LIGHTTYPE_POINT = 11;
const int acgm::SceneImporter::LIGHTTYPE_SPOT = 12;
const int acgm::SceneImporter::SHADERTYPE_PHONG = 50;
const int acgm::SceneImporter::SHADERTYPE_CHECKER = 51;

bool acgm::SceneImporter::Import(const std::string &filename)
{
  stream_.open(filename);
  if (!stream_.good())
  {
    stream_.close();
    dialog::Error("Can not import file " + filename + ". File can not be opened.");
    return false;
  }

  render_options_ = ReadRenderOptions();
  scene_ = ReadScene();

  stream_.close();
  return true;
}

std::shared_ptr<acgm::Scene> acgm::SceneImporter::GetScene() const
{
  return scene_;
}

acgm::RenderOptions acgm::SceneImporter::GetRenderOptions() const
{
  return render_options_;
}

std::string acgm::SceneImporter::GetLine()
{
  std::string line;
  std::getline(stream_, line);
  return line;
}

float acgm::SceneImporter::ReadFloat()
{
  float result;
  stream_ >> result;
  return result;
}

glm::vec3 acgm::SceneImporter::ReadVec3()
{
  glm::vec3 result;
  stream_ >> result.x >> result.y >> result.z;
  return result;
}

glm::mat4 acgm::SceneImporter::ReadMat4()
{
  glm::mat4 result;
  for (size_t i = 0; i < 4; ++i)
  {
    stream_ >> result[i].x >> result[i].y >> result[i].z >> result[i].w;
  }
  return result;
}

cogs::Color3f acgm::SceneImporter::ReadColor()
{
  cogs::Color3f result;
  stream_ >> result.r >> result.g >> result.b;
  return result;
}

acgm::RenderOptions acgm::SceneImporter::ReadRenderOptions()
{
  RenderOptions result;
  stream_ >> result.resolution.x >> result.resolution.y;
  GetLine();
  return result;
}

std::shared_ptr<acgm::Camera> acgm::SceneImporter::ReadCamera()
{
  const auto position = ReadVec3();
  const auto up_direction = ReadVec3();
  const auto forward_direction = ReadVec3();
  const auto z_near = ReadFloat();
  const auto z_far = ReadFloat();
  const auto fov_y_rad = ReadFloat();
  GetLine();

  //convert radians to degrees
  float fovDegrees  = fov_y_rad * 180.0f / 3.14f;
  // #TODO Create and return instance of your camera object
  std::shared_ptr<acgm::Camera> camera = std::make_shared<acgm::Camera>(
      position, up_direction, forward_direction,
      z_near, z_far, fovDegrees);
  return camera;
}

std::shared_ptr<acgm::Model> acgm::SceneImporter::ReadModel()
{
  int model_type;
  stream_ >> model_type;

  std::shared_ptr<acgm::Model> model;
  const auto model_name = GetLine();
  if (model_type == MODELTYPE_PLANE)
  {
    const auto position = ReadVec3();
    const auto normal = ReadVec3();
    //model = #TODO new instance of Plane object
    model = std::make_shared<acgm::Plane>(position, normal);
  }
  if (model_type == MODELTYPE_SPHERE)
  {
    const auto position = ReadVec3();
    const auto radius = ReadFloat();
    // model = #TODO new instance of Sphere object
    model = std::make_shared<acgm::Sphere>(position, radius);
  }
  if (model_type == MODELTYPE_MESH)
  {
    auto file_name = GetLine();
    std_ext::Trim(file_name);
    const auto transform = ReadMat4();
    // model = #TODO new instance of Mesh object
    model = std::make_shared<acgm::Mesh>(file_name, transform);
  }
  model->name_ = model_name;
  GetLine();

  const auto shader = ReadShader();
  model->SetShader(shader);
  return model;
}

std::vector<std::shared_ptr<acgm::Model>> acgm::SceneImporter::ReadModels()
{
  size_t models_count;
  stream_ >> models_count;
  std::vector<std::shared_ptr<Model>> models;
  models.reserve(models_count);
  for (size_t i = 0; i < models_count; ++i)
  {
    models.push_back(ReadModel());
  }
  return models;
}

std::shared_ptr<acgm::Shader> acgm::SceneImporter::ReadShader()
{
  std::shared_ptr<acgm::Shader> shader;
  int shader_type;
  stream_ >> shader_type;
  if (shader_type == SHADERTYPE_PHONG)
  {
    const auto color = ReadColor();
    const auto shininess = ReadFloat();
    const auto ambient = ReadFloat();
    const auto diffuse = ReadFloat();
    const auto specular = ReadFloat();
    const auto glossiness = ReadFloat(); // #UNLOCKED at Reflection seminar
    const auto transparency = ReadFloat(); // #UNLOCKED at Transparency seminar
    const auto refractive_index = ReadFloat(); // #UNLOCKED at Transparency seminar
    GetLine();
    // shader = #TODO new instance of PhongShader object
    shader = std::make_shared<PhongShader>(color, shininess, ambient, diffuse, specular,
        glossiness, transparency, refractive_index);
  }
  if (shader_type == SHADERTYPE_CHECKER)
  {
    const auto cube_size = ReadFloat();
    const auto shader0 = ReadShader();
    const auto shader1 = ReadShader();
    shader =  std::make_shared<CheckerBoardShader>(shader0, shader1, cube_size);
  }
  return shader;
}

std::shared_ptr<acgm::Light> acgm::SceneImporter::ReadLight()
{
  std::shared_ptr<acgm::Light> light;
  int light_type;
  stream_ >> light_type;
  if (light_type == LIGHTTYPE_SUN)
  {
    const auto intensity = ReadFloat();
    const auto direction = ReadVec3();
    // light = #TODO new instance of SunLight object
    light = std::make_shared<DirectionalLight>(intensity, direction);
  }
  if (light_type == LIGHTTYPE_POINT)
  {
    const auto intensity = ReadFloat();
    const auto position = ReadVec3();
    const auto range = ReadFloat();
    const auto linear_attenuation = ReadFloat();
    const auto quadratic_attenuation = ReadFloat();
    light = std::make_shared<PointLight>(intensity, position, range, linear_attenuation, quadratic_attenuation);
  }
  if (light_type == LIGHTTYPE_SPOT)
  {
    const auto intensity = ReadFloat();
    const auto position = ReadVec3();
    const auto range = ReadFloat();
    const auto linear_attenuation = ReadFloat();
    const auto quadratic_attenuation = ReadFloat();
    const auto spot_direction = ReadVec3();
    const auto cutoff_angle = ReadFloat();
    const auto exponent = ReadFloat();
    light = std::make_shared<SpotLight>(intensity, position, range, linear_attenuation, quadratic_attenuation,
        spot_direction, cutoff_angle, exponent);
  }
  GetLine();
  return light;
}

std::shared_ptr<acgm::Scene> acgm::SceneImporter::ReadScene()
{
  const auto bias = ReadFloat();
  const auto index_of_refraction = ReadFloat(); // #UNLOCKED at Transparency seminar
  const auto enviro_up = ReadVec3();            // #UNLOCKED at Environment seminar
  const auto enviro_seam = ReadVec3();          // #UNLOCKED at Environment seminar
  auto enviro_image_file = GetLine();           // #UNLOCKED at Environment seminar
  std_ext::Trim(enviro_image_file);
  const auto camera = ReadCamera();
  const auto light = ReadLight();
  const auto models = ReadModels();

  // #TODO Create your scene object and set imported camera, light and models to it
  std::shared_ptr<Scene> scene = std::make_shared<Scene>(camera, light, models, enviro_image_file,
      enviro_up, enviro_seam, index_of_refraction);
  return scene;
}
