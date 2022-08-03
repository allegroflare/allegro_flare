

#include <AllegroFlare/InputHints.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{


InputHints::InputHints(AllegroFlare::FontBin* font_bin)
   : font_bin(font_bin)
   , input_hints({})
{
}


InputHints::~InputHints()
{
}


void InputHints::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "InputHints" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "InputHints" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_ttf_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "InputHints" << "::" << "render" << ": error: " << "guard \"al_is_ttf_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_primitives_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "InputHints" << "::" << "render" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   int surface_width = 1920;
   int surface_height = 1080;

   // draw inputs
   float height = 60;
   float hud_opacity = 0.35;
   ALLEGRO_COLOR backfill_color = ALLEGRO_COLOR{0, 0, 0, hud_opacity};
   al_draw_filled_rectangle(0, surface_height-height, surface_width, surface_height, backfill_color);

   // draw inputs text
   ALLEGRO_FONT *font = obtain_font();
   std::string SPACER = "         ";
   std::string inputs = "[W/A/S/D]  Move cursor"
                      + SPACER + "[N/P]  Next/Previous entity"
                      + SPACER + "[Shift+8]  Capture screenshot"
                      + SPACER + "[PAD +/-]  Zoom"
                      + SPACER + "[ESC]  Toggle Inventory"
                      + SPACER + "[-/+]  Change time of day";
   float text_height = al_get_font_line_height(font);
   al_draw_text(
      font,
      ALLEGRO_COLOR{1, 1, 1, 1},
      surface_width/2,
      (int)(surface_height-text_height/2-height/2),
      ALLEGRO_ALIGN_CENTER,
      inputs.c_str()
   );
   return;
}

std::vector<std::pair<std::string, std::string>> InputHints::build_placeholder_input_hints()
{
   return std::vector<std::pair<std::string, std::string>>{
      { "[W/A/S/D]", "Move cursor" },
      { "[N/P]",     "Next/Previous entity" },
      { "[Shift+8]", "Capture screenshot" },
      { "[PAD +/-]", "Zoom" },
      { "[ESC]",     "Toggle Inventory" },
      { "[-/+]",     "Change time of day" },
   };
}

ALLEGRO_FONT* InputHints::obtain_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "InputHints" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::string font_name = "Inter-Medium.ttf";
   int font_size = -20;

   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << font_size;
   return font_bin->auto_get(composite_font_str.str());
}
} // namespace AllegroFlare


