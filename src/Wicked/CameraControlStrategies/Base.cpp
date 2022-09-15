

#include <Wicked/CameraControlStrategies/Base.hpp>

#include <sstream>
#include <stdexcept>


namespace Wicked
{
namespace CameraControlStrategies
{


Base::Base(AllegroFlare::Placement2D* camera)
   : camera(camera)
   , initialized(false)
{
}


Base::~Base()
{
}


void Base::set_camera(AllegroFlare::Placement2D* camera)
{
   this->camera = camera;
}


AllegroFlare::Placement2D* Base::get_camera() const
{
   return camera;
}


bool Base::get_initialized() const
{
   return initialized;
}


AllegroFlare::Placement2D* &Base::get_camera_ref()
{
   return camera;
}


void Base::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "Base" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   initialized = true;
   return;
}

void Base::update()
{
   return;
}


} // namespace CameraControlStrategies
} // namespace Wicked


