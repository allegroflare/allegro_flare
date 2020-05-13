

#include <AllegroFlare/FrameworkScreenRegistrar.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{


FrameworkScreenRegistrar::FrameworkScreenRegistrar(AllegroFlare::Screens* screens, AllegroFlare::Screen* screen)
   : screens(screens)
   , screen(screen)
{
}


FrameworkScreenRegistrar::~FrameworkScreenRegistrar()
{
}


bool FrameworkScreenRegistrar::append()
{
if (!(screens))
   {
      std::stringstream error_message;
      error_message << "FrameworkScreenRegistrar" << "::" << "append" << ": error: " << "guard \"screens\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(screen))
   {
      std::stringstream error_message;
      error_message << "FrameworkScreenRegistrar" << "::" << "append" << ": error: " << "guard \"screen\" not met";
      throw std::runtime_error(error_message.str());
   }
screens->add(screen);
return true;

}

bool FrameworkScreenRegistrar::remove()
{
if (!(screens))
   {
      std::stringstream error_message;
      error_message << "FrameworkScreenRegistrar" << "::" << "remove" << ": error: " << "guard \"screens\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(screen))
   {
      std::stringstream error_message;
      error_message << "FrameworkScreenRegistrar" << "::" << "remove" << ": error: " << "guard \"screen\" not met";
      throw std::runtime_error(error_message.str());
   }
screens->remove(screen);
return true;

}
} // namespace AllegroFlare


