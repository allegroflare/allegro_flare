

#include <AllegroFlare/Elements/ScrollBar.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{


ScrollBar::ScrollBar()
   : quote({})
{
}


ScrollBar::~ScrollBar()
{
}


void ScrollBar::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "ScrollBar" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_primitives_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "ScrollBar" << "::" << "render" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   return;
}
} // namespace Elements
} // namespace AllegroFlare


