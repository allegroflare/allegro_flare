

#include <AllegroFlare/Elements/DialogBoxNameTag.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <AllegroFlare/Elements/DialogBoxFrame.hpp>
#include <stdexcept>
#include <sstream>
#include <allegro5/allegro_color.h>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{


DialogBoxNameTag::DialogBoxNameTag(AllegroFlare::FontBin* font_bin, std::string name, float width, float height)
   : font_bin(font_bin)
   , name(name)
   , width(width)
   , height(height)
{
}


DialogBoxNameTag::~DialogBoxNameTag()
{
}


float DialogBoxNameTag::get_width()
{
   return width;
}


float DialogBoxNameTag::get_height()
{
   return height;
}


void DialogBoxNameTag::render()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "DialogBoxNameTag" << "::" << "render" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "DialogBoxNameTag" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_primitives_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "DialogBoxNameTag" << "::" << "render" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_get_current_display()))
      {
         std::stringstream error_message;
         error_message << "DialogBoxNameTag" << "::" << "render" << ": error: " << "guard \"al_get_current_display()\" not met";
         throw std::runtime_error(error_message.str());
      }
   AllegroFlare::Elements::DialogBoxFrame(width, height).render();
   draw_text();
   return;
}

void DialogBoxNameTag::draw_text()
{
   ALLEGRO_FONT* font = obtain_dialog_font();
   ALLEGRO_COLOR text_color = al_color_html("ffffff");
   al_draw_text(
      font,
      text_color,
      width/2,
      height/2 - al_get_font_line_height(font)/2 - 2,
      ALLEGRO_ALIGN_CENTER,
      name.c_str()
   );
   return;
}

ALLEGRO_FONT* DialogBoxNameTag::obtain_dialog_font()
{
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "DialogBoxNameTag" << "::" << "obtain_dialog_font" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_ttf_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "DialogBoxNameTag" << "::" << "obtain_dialog_font" << ": error: " << "guard \"al_is_ttf_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "DialogBoxNameTag" << "::" << "obtain_dialog_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   static const std::string FONT_IDENTIFIER = "Inter-Medium.ttf -36";
   ALLEGRO_FONT* result_font = font_bin->operator[](FONT_IDENTIFIER);
   return result_font;
}
} // namespace Elements
} // namespace AllegroFlare


