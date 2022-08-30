

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


DialogRollRenderer::DialogRollRenderer(AllegroFlare::FontBin* font_bin, std::vector<std::pair<std::string, std::string>> roll, float width)
   : font_bin(font_bin)
   , roll(roll)
   , width(width)
   , gutter_x(400)
   , gutter_padding(20)
   , speaker_color(ALLEGRO_COLOR{1, 1, 1, 1})
   , dialog_color(ALLEGRO_COLOR{1, 1, 1, 1})
   , internal_dialog_color(ALLEGRO_COLOR{1, 1, 1, 1})
{
}


DialogRollRenderer::~DialogRollRenderer()
{
}


void DialogRollRenderer::set_width(float width)
{
   this->width = width;
}


void DialogRollRenderer::set_gutter_x(float gutter_x)
{
   this->gutter_x = gutter_x;
}


void DialogRollRenderer::set_gutter_padding(float gutter_padding)
{
   this->gutter_padding = gutter_padding;
}


void DialogRollRenderer::set_speaker_color(ALLEGRO_COLOR speaker_color)
{
   this->speaker_color = speaker_color;
}


void DialogRollRenderer::set_dialog_color(ALLEGRO_COLOR dialog_color)
{
   this->dialog_color = dialog_color;
}


void DialogRollRenderer::set_internal_dialog_color(ALLEGRO_COLOR internal_dialog_color)
{
   this->internal_dialog_color = internal_dialog_color;
}


float DialogRollRenderer::get_width() const
{
   return width;
}


float DialogRollRenderer::get_gutter_x() const
{
   return gutter_x;
}


float DialogRollRenderer::get_gutter_padding() const
{
   return gutter_padding;
}


ALLEGRO_COLOR DialogRollRenderer::get_speaker_color() const
{
   return speaker_color;
}


ALLEGRO_COLOR DialogRollRenderer::get_dialog_color() const
{
   return dialog_color;
}


ALLEGRO_COLOR DialogRollRenderer::get_internal_dialog_color() const
{
   return internal_dialog_color;
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
   ALLEGRO_FONT *text_font = obtain_font();
   ALLEGRO_FONT *internal_dialog_font = obtain_italic_font();
   for (auto &roll_item : roll)
   {
      std::string speaker = std::get<0>(roll_item);
      std::string dialog = std::get<1>(roll_item);

      bool is_internal_speaker = speaker.empty() || speaker == AllegroFlare::Elements::DialogRoll::SPEAKER_INTERNAL;

      ALLEGRO_FONT *dialog_font = is_internal_speaker ? internal_dialog_font : text_font;

      if (!is_internal_speaker)
      {
         // draw the speaker
         float multiline_text_width = gutter_x;
         float line_height = al_get_font_line_height(text_font);

         al_draw_multiline_text(
            text_font,
            speaker_color,
            gutter_x-gutter_padding,
            cursor_y,
            multiline_text_width,
            line_height,
            ALLEGRO_ALIGN_RIGHT,
            speaker.c_str()
         );
      }

      // draw the spoken dialog
      float multiline_text_width = width - gutter_x;
      float line_height = al_get_font_line_height(text_font);

      al_draw_multiline_text(
         dialog_font,
         speaker_color,
         gutter_x+gutter_padding,
         cursor_y,
         multiline_text_width,
         line_height,
         ALLEGRO_ALIGN_LEFT,
         dialog.c_str()
      );

      // TODO: properly increment height on each section
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


