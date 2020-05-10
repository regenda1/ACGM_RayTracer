#include <ACGM_RayTracer_lib/Image.h>
#define STB_IMAGE_IMPLEMENTATION
#include <ACGM_RayTracer_lib/stb_image.h>

acgm::Image::Image(std::string filename)
{
  imgData_ = stbi_load(filename.c_str(), &width_, &height_, &channels_, 3);
}

cogs::Color3f acgm::Image::GetColorAt(const glm::vec2 &uvs) const
{
  int x = floor((width_ * uvs.y));
  int y = floor((height_ * uvs.x));
  int pixel = (y * width_ + x) * 3;
  //std::cout << "r " << imgData_[pixel + 0] << "g " << imgData_[pixel + 1] << "b " << imgData_[pixel + 2] << std::endl;
  return cogs::Color3b(imgData_[pixel + 0], imgData_[pixel + 1], imgData_[pixel + 2]);
}

/*
  cogs::Color3f acgm::Image::MapImage(Ray &r) const
  {
	// compute background color
	cogs::Color3f background_color;
	if (filename_.length() == 0)
	{
		background_color = cogs::color::BLACK;
	}
	else
	{
		//longitude computation
		glm::vec3 x = glm::dot(enviroUp_, r.getD()) * enviroUp_;
		x = r.getD() - x;
		x = glm::normalize(x);
		//float lonAngle = glm::acos(glm::dot(enviroSeam_, x));
		float lonAngle = glm::orientedAngle(x, enviroSeam_, enviroUp_);
		lonAngle += glm::pi<float>();
		lonAngle /= glm::pi<float>() * 2.0f;
		//latitude computation
		float latAngle = glm::acos(glm::dot(enviroUp_, r.getD())) / glm::pi<float>();
		background_color = image_->GetColorAt(glm::vec2(latAngle, lonAngle));
	}
	return background_color;
  }
*/