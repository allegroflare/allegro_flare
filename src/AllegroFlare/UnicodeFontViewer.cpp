

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


UnicodeFontViewer::UnicodeFontViewer(AllegroFlare::FontBin* font_bin, std::string font_identifier, int32_t unicode_range_start)
   : font_bin(font_bin)
   , font_identifier(font_identifier)
   , unicode_range_start(unicode_range_start)
{
}


UnicodeFontViewer::~UnicodeFontViewer()
{
}


void UnicodeFontViewer::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void UnicodeFontViewer::set_font_identifier(std::string font_identifier)
{
   this->font_identifier = font_identifier;
}


void UnicodeFontViewer::set_unicode_range_start(int32_t unicode_range_start)
{
   this->unicode_range_start = unicode_range_start;
}


std::string UnicodeFontViewer::get_font_identifier()
{
   return font_identifier;
}


int32_t UnicodeFontViewer::get_unicode_range_start()
{
   return unicode_range_start;
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
   int32_t unicode_range_end = unicode_range_start+0x00ff; // unicode_range_start to unicode_range_start+255
   ALLEGRO_FONT *ui_font = obtain_ui_font();
   ALLEGRO_FONT *ui_font_mini = obtain_ui_font_mini();
   ALLEGRO_FONT *unicode_font = obtain_unicode_font();
   ALLEGRO_COLOR white = AllegroFlare::Color::White;
   ALLEGRO_COLOR black = AllegroFlare::Color::Black;
   std::stringstream range_string;

   range_string << "you are currently viewing the range " << unicode_range_start << "-" << unicode_range_end;

   al_draw_text(ui_font, white, 20, 20, 0, "Press the RIGHT ARROW and LEFT ARROW keys to flip through the pages");
   al_draw_text(ui_font, white, 20, 60, 0, range_string.str().c_str());

   int table_y = 180;
   int table_x = 100;
   int line = 0;
   int num_columns = 32;

   int line_height = 80;
   int column_width = 52;

   int row = 0;
   for (int32_t character=unicode_range_start; character<=unicode_range_end; character++)
   {
      int x = table_x + row*column_width;
      int y = table_y + line*line_height;
      float column_middle_int = (int)(x + column_width*0.5);

      draw_unicode_character(unicode_font, white, character, ALLEGRO_ALIGN_CENTER, x, y);

      std::stringstream character_number_as_str;
      character_number_as_str << character;
      al_draw_text(ui_font_mini, white, column_middle_int, y, 0, character_number_as_str.str().c_str());

      row += 1;
      if (row > num_columns) { row = 0; line++; }
   }
}

void UnicodeFontViewer::previous_page()
{
   unicode_range_start -= 0x0100; // 256 characters per page
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
   std::stringstream font_identifier_and_size;
   font_identifier_and_size << font_identifier << " 42";
   return font_bin->auto_get(font_identifier_and_size.str().c_str());
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


