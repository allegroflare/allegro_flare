

#include <AllegroFlare/UnicodeFontViewer.hpp>
#include <AllegroFlare/Color.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_font.h>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{


UnicodeFontViewer::UnicodeFontViewer(AllegroFlare::FontBin* font_bin)
   : font_bin(font_bin)
   , unicode_range_start(0x1D100)
{
}


UnicodeFontViewer::~UnicodeFontViewer()
{
}


void UnicodeFontViewer::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void UnicodeFontViewer::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "UnicodeFontViewer" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "UnicodeFontViewer" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_ttf_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "UnicodeFontViewer" << "::" << "render" << ": error: " << "guard \"al_is_ttf_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "UnicodeFontViewer" << "::" << "render" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   int32_t unicode_range_end = unicode_range_start+0x00ff;
   ALLEGRO_FONT *ui_font = obtain_ui_font();
   ALLEGRO_FONT *ui_font_mini = obtain_ui_font_mini();
   ALLEGRO_FONT *unicode_font = obtain_unicode_font();
   ALLEGRO_COLOR white = AllegroFlare::Color::White;
   ALLEGRO_COLOR black = AllegroFlare::Color::Black;
   std::stringstream range_string;

   range_string << "you are currently viewing the range " << unicode_range_start << "-" << unicode_range_end;

   al_draw_text(ui_font, white, 20, 20, 0, "Press the RIGHT ARROW and LEFT ARROW keys to flip through the pages");
   al_draw_text(ui_font, white, 20, 60, 0, range_string.str().c_str());

   //int y=90;
   int line = 0;
   int num_rows = 30;
   int line_height = 80;
   int row_width = 45;
   int row = 0;
   for (int32_t character=unicode_range_start; character<=unicode_range_end; character++)
   {
      int x = 100 + row*row_width;
      int y = 100 + line*line_height;
      draw_unicode_character(unicode_font, white, character, ALLEGRO_ALIGN_CENTER, x, y);
      std::stringstream character_number_as_str;
      character_number_as_str << character;
      al_draw_text(ui_font_mini, white, x, y, 0, character_number_as_str.str().c_str());
      row += 1;
      if (row > num_rows) { row = 0; line++; }
   }
}

void UnicodeFontViewer::previous_page()
{
   unicode_range_start -= 0x0100;
   return;
}

void UnicodeFontViewer::next_page()
{
   unicode_range_start += 0x0100;
   return;
}

void UnicodeFontViewer::draw_unicode_character(ALLEGRO_FONT* font, ALLEGRO_COLOR color, int32_t icon, int flags, float x, float y)
{
   static ALLEGRO_USTR *ustr = NULL;
   if (!ustr) ustr = al_ustr_new("");
   al_ustr_set_chr(ustr, 0, icon);
   al_draw_ustr(font, color, x, y, flags, ustr);
   return;
}

ALLEGRO_FONT* UnicodeFontViewer::obtain_unicode_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "UnicodeFontViewer" << "::" << "obtain_unicode_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("fa-solid-900.ttf 40");
}

ALLEGRO_FONT* UnicodeFontViewer::obtain_ui_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "UnicodeFontViewer" << "::" << "obtain_ui_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("Inter-Medium.ttf 20");
}

ALLEGRO_FONT* UnicodeFontViewer::obtain_ui_font_mini()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "UnicodeFontViewer" << "::" << "obtain_ui_font_mini" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("Inter-Medium.ttf 9");
}
} // namespace AllegroFlare


