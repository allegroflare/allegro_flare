

#include <AllegroFlare/CameraControlStrategies2D/Base.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace CameraControlStrategies2D
{


Base::Base(std::string type, AllegroFlare::Camera2D* camera)
   : type(type)
   , camera(camera)
   , initialized(false)
{
}


Base::~Base()
{
}


void Base::set_camera(AllegroFlare::Camera2D* camera)
{
   this->camera = camera;
}


std::string Base::get_type() const
{
   return type;
}


AllegroFlare::Camera2D* Base::get_camera() const
{
   return camera;
}


bool Base::get_initialized() const
{
   return initialized;
}


AllegroFlare::Camera2D* &Base::get_camera_ref()
{
   return camera;
}


bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}

void Base::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Base::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::initialize: error: guard \"(!initialized)\" not met");
   }
   initialized = true;
   return;
}

void Base::update()
{
   return;
}


} // namespace CameraControlStrategies2D
} // namespace AllegroFlare


