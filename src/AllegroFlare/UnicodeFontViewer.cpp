

#include <AllegroFlare/UnicodeFontViewer.hpp>

#include <AllegroFlare/Color.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


UnicodeFontViewer::UnicodeFontViewer(AllegroFlare::FontBin* font_bin, std::string font_identifier, uint32_t unicode_range_start)
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


void UnicodeFontViewer::set_unicode_range_start(uint32_t unicode_range_start)
{
   this->unicode_range_start = unicode_range_start;
}


std::string UnicodeFontViewer::get_font_identifier() const
{
   return font_identifier;
}


uint32_t UnicodeFontViewer::get_unicode_range_start() const
{
   return unicode_range_start;
}


void UnicodeFontViewer::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::UnicodeFontViewer::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::UnicodeFontViewer::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::UnicodeFontViewer::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::UnicodeFontViewer::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::UnicodeFontViewer::render]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::UnicodeFontViewer::render]: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::UnicodeFontViewer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::UnicodeFontViewer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::UnicodeFontViewer::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::UnicodeFontViewer::render]: error: guard \"font_bin\" not met");
   }
   uint32_t unicode_range_end = unicode_range_start+0x00ff; // unicode_range_start to unicode_range_start+255
   ALLEGRO_FONT *ui_font = obtain_ui_font();
   ALLEGRO_FONT *ui_font_mini = obtain_ui_font_mini();
   ALLEGRO_FONT *unicode_font = obtain_unicode_font();
   ALLEGRO_COLOR white = AllegroFlare::Color::White;
   ALLEGRO_COLOR black = AllegroFlare::Color::Black;
   std::stringstream range_string;
   int font_line_height = al_get_font_line_height(unicode_font);
   int h_font_line_height_int = (int)(font_line_height * 0.5);
   int ui_font_mini_line_height = al_get_font_line_height(ui_font_mini);

   range_string << "you are currently viewing the range "
                << as_hex(unicode_range_start)
                << "-"
                << as_hex(unicode_range_end)
                ;

   al_draw_text(ui_font, white, 20, 20, 0, "Press the RIGHT ARROW and LEFT ARROW keys to flip through the pages");
   al_draw_text(ui_font, white, 20, 60, 0, range_string.str().c_str());

   int table_y = 120;
   int table_x = 100;
   int line = 0;
   int num_columns = 32;

   int row_height = 112;
   int column_width = 54;

   int column = 0;
   for (uint32_t character=unicode_range_start; character<=unicode_range_end; character++)
   {
      int x = table_x + column*column_width;
      int y = table_y + line*row_height;
      float column_middle_int = (int)(x + column_width*0.5);

      al_draw_rectangle(x, y, x+column_width, y+row_height, ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2}, 1.0);

      draw_unicode_character(unicode_font, white, character, ALLEGRO_ALIGN_CENTER, column_middle_int, y);

      // draw hex number
      al_draw_text(
         ui_font_mini,
         white,
         column_middle_int,
         y+row_height-ui_font_mini_line_height - 4,
         ALLEGRO_ALIGN_CENTER,
         as_hex(character).c_str()
      );

      // draw int number
      al_draw_text(
         ui_font_mini,
         white,
         column_middle_int,
         y+row_height-(ui_font_mini_line_height*2) - 4,
         ALLEGRO_ALIGN_CENTER,
         as_int(character).c_str()
      );

      column += 1;
      if (column >= num_columns) { column = 0; line++; }
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

std::string UnicodeFontViewer::as_hex(uint32_t value, int zero_fill_width)
{
   std::stringstream ss;
   ss << "0x" << std::uppercase << std::setfill('0') << std::setw(zero_fill_width) << std::hex << value;
   return ss.str();
}

std::string UnicodeFontViewer::as_int(uint32_t value)
{
   std::stringstream ss;
   ss << value;
   return ss.str();
}

void UnicodeFontViewer::draw_unicode_character(ALLEGRO_FONT* font, ALLEGRO_COLOR color, uint32_t icon, int flags, float x, float y)
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
      error_message << "[AllegroFlare::UnicodeFontViewer::obtain_unicode_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::UnicodeFontViewer::obtain_unicode_font]: error: guard \"font_bin\" not met");
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
      error_message << "[AllegroFlare::UnicodeFontViewer::obtain_ui_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::UnicodeFontViewer::obtain_ui_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Regular.ttf 20");
}

ALLEGRO_FONT* UnicodeFontViewer::obtain_ui_font_mini()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::UnicodeFontViewer::obtain_ui_font_mini]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::UnicodeFontViewer::obtain_ui_font_mini]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Regular.ttf 10");
}


} // namespace AllegroFlare


