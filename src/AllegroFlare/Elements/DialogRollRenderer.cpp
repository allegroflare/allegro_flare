

#include <AllegroFlare/Elements/DialogRollRenderer.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{


DialogRollRenderer::DialogRollRenderer(AllegroFlare::FontBin* font_bin, AllegroFlare::Elements::DialogRoll* dialog_roll)
   : font_bin(font_bin)
   , dialog_roll(dialog_roll)
{
}


DialogRollRenderer::~DialogRollRenderer()
{
}


void DialogRollRenderer::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "DialogRollRenderer" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "DialogRollRenderer" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   return;
}

ALLEGRO_FONT* DialogRollRenderer::obtain_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "DialogRollRenderer" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("Lora-Medium.ttf -28");
}

ALLEGRO_FONT* DialogRollRenderer::obtain_italic_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "DialogRollRenderer" << "::" << "obtain_italic_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("Lora-MediumItalic.ttf -28");
}
} // namespace Elements
} // namespace AllegroFlare


