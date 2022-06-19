

#include <AllegroFlare/Elements/Text.hpp>
#include <allegro5/allegro.h>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{


Text::Text(AllegroFlare::FontBin* font_bin)
   : font_bin(font_bin)
   , quote({})
{
}


Text::~Text()
{
}


void Text::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "Text" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "Text" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   ALLEGRO_COLOR color = ALLEGRO_COLOR{1, 1, 1, 1};
   float x = 20;
   float y = 20;
   int flags = 0;
   al_draw_text(obtain_font(), color, x, y, flags, "Hello Text");
   return;
}

ALLEGRO_FONT* Text::obtain_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Text" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("DroidSans.ttf -48");
}
} // namespace Elements
} // namespace AllegroFlare


