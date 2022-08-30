

#include <AllegroFlare/Elements/DialogRollRenderer.hpp>
#include <AllegroFlare/Elements/DialogRoll.hpp>
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


DialogRollRenderer::DialogRollRenderer(AllegroFlare::FontBin* font_bin, std::vector<std::pair<std::string, std::string>> roll)
   : font_bin(font_bin)
   , roll(roll)
   , gutter_x(500)
   , width(1500)
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
   float y_offset = 0;
   float cursor_y = 0 + y_offset;
   float gutter = 20;
   ALLEGRO_FONT *text_font = obtain_font();
   ALLEGRO_FONT *internal_dialog_font = obtain_italic_font();
   for (auto &roll_item : roll)
   {
      std::string speaker = std::get<0>(roll_item);
      std::string dialog = std::get<1>(roll_item);
      ALLEGRO_COLOR speaker_color = ALLEGRO_COLOR{1, 1, 1, 1};
      ALLEGRO_COLOR dialog_color = ALLEGRO_COLOR{1, 1, 1, 1};
      ALLEGRO_COLOR internal_dialog_color = ALLEGRO_COLOR{1, 1, 1, 1};

      bool is_internal_speaker = speaker.empty() || speaker == AllegroFlare::Elements::DialogRoll::SPEAKER_INTERNAL;

      ALLEGRO_FONT *dialog_font = is_internal_speaker ? internal_dialog_font : text_font;

      if (!is_internal_speaker)
      {
         float multiline_text_width = width - gutter_x;
         float line_height = al_get_font_line_height(text_font);
         al_draw_multiline_text(
            text_font,
            speaker_color,
            gutter_x-gutter,
            cursor_y,
            multiline_text_width,
            line_height,
            ALLEGRO_ALIGN_RIGHT,
            speaker.c_str()
         );
      }

      float multiline_text_width = gutter_x;
      float line_height = al_get_font_line_height(text_font);

      al_draw_multiline_text(
         dialog_font,
         speaker_color,
         gutter_x+gutter,
         cursor_y,
         multiline_text_width,
         line_height,
         ALLEGRO_ALIGN_LEFT,
         dialog.c_str()
      );

      cursor_y += 72;
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
   return font_bin->auto_get("Lora-Medium.ttf -48");
}

ALLEGRO_FONT* DialogRollRenderer::obtain_italic_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "DialogRollRenderer" << "::" << "obtain_italic_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("Lora-MediumItalic.ttf -48");
}
} // namespace Elements
} // namespace AllegroFlare


