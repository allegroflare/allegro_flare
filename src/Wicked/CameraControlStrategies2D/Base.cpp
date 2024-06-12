

#include <Wicked/CameraControlStrategies2D/Base.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Wicked
{
namespace CameraControlStrategies2D
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
      error_message << "[Wicked::CameraControlStrategies2D::Base::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::CameraControlStrategies2D::Base::initialize]: error: guard \"(!initialized)\" not met");
   }
   initialized = true;
   return;
}

void Base::update()
{
   return;
}


} // namespace CameraControlStrategies2D
} // namespace Wicked


