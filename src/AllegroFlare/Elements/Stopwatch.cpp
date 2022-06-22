

#include <AllegroFlare/Elements/Stopwatch.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{


Stopwatch::Stopwatch(AllegroFlare::FontBin* font_bin)
   : font_bin(font_bin)
   , quote({})
{
}


Stopwatch::~Stopwatch()
{
}


void Stopwatch::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "Stopwatch" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "Stopwatch" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Stopwatch" << "::" << "render" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return;
}

ALLEGRO_FONT* Stopwatch::obtain_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Stopwatch" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("Purista Medium.otf -32");
}
} // namespace Elements
} // namespace AllegroFlare


