

#include <AllegroFlare/Elements/HealthBars/Classic.hpp>
#include <allegro5/allegro.h>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{
namespace HealthBars
{


Classic::Classic(AllegroFlare::FontBin* font_bin)
   : font_bin(font_bin)
   , quote({})
{
}


Classic::~Classic()
{
}


void Classic::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "Classic" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "Classic" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   ALLEGRO_COLOR color = ALLEGRO_COLOR{1, 1, 1, 1};
   float x = 20;
   float y = 20;
   int flags = 0;
   al_draw_text(obtain_font(), color, x, y, flags, "Hello Text");
   return;
}

ALLEGRO_FONT* Classic::obtain_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Classic" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("DroidSans.ttf -48");
}
} // namespace HealthBars
} // namespace Elements
} // namespace AllegroFlare


