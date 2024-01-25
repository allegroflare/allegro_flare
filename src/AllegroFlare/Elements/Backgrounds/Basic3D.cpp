

#include <AllegroFlare/Elements/Backgrounds/Basic3D.hpp>

#include <AllegroFlare/Placement2D.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace Backgrounds
{


Basic3D::Basic3D()
   : AllegroFlare::Elements::Backgrounds::Base(AllegroFlare::Elements::Backgrounds::Basic3D::TYPE)
   , bitmap_bin(nullptr)
   , model_bin(nullptr)
   , scene({})
   , initialized(false)
{
}


Basic3D::~Basic3D()
{
}


void Basic3D::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void Basic3D::set_model_bin(AllegroFlare::ModelBin* model_bin)
{
   this->model_bin = model_bin;
}


AllegroFlare::BitmapBin* Basic3D::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::ModelBin* Basic3D::get_model_bin() const
{
   return model_bin;
}


AllegroFlare::GraphicsPipelines::Basic3D::Scene& Basic3D::get_scene_ref()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Basic3D::get_scene_ref]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic3D::get_scene_ref: error: guard \"initialized\" not met");
   }
   // TODO: Test this guard
   return scene;
}

void Basic3D::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Basic3D::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic3D::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(model_bin))
   {
      std::stringstream error_message;
      error_message << "[Basic3D::initialize]: error: guard \"model_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic3D::initialize: error: guard \"model_bin\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[Basic3D::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic3D::initialize: error: guard \"bitmap_bin\" not met");
   }
   scene.set_bitmap_bin(bitmap_bin);
   scene.set_model_bin(model_bin);
   scene.initialize();
   initialized = true;
   return;
}

void Basic3D::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Basic3D::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic3D::render: error: guard \"initialized\" not met");
   }
   return;
}


} // namespace Backgrounds
} // namespace Elements
} // namespace AllegroFlare


