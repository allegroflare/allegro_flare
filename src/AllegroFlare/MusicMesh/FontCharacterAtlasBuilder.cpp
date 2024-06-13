

#include <AllegroFlare/MusicMesh/FontCharacterAtlasBuilder.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_primitives.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace MusicMesh
{


FontCharacterAtlasBuilder::FontCharacterAtlasBuilder(AllegroFlare::FontBin* font_bin, std::string font_identifier, int font_size)
   : font_bin(font_bin)
   , font_identifier(font_identifier)
   , font_size(font_size)
   , row_height(160)
   , column_width(54)
{
}


FontCharacterAtlasBuilder::~FontCharacterAtlasBuilder()
{
}


void FontCharacterAtlasBuilder::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void FontCharacterAtlasBuilder::set_font_identifier(std::string font_identifier)
{
   this->font_identifier = font_identifier;
}


void FontCharacterAtlasBuilder::set_font_size(int font_size)
{
   this->font_size = font_size;
}


std::string FontCharacterAtlasBuilder::get_font_identifier() const
{
   return font_identifier;
}


int FontCharacterAtlasBuilder::get_font_size() const
{
   return font_size;
}


int FontCharacterAtlasBuilder::get_row_height() const
{
   return row_height;
}


int FontCharacterAtlasBuilder::get_column_width() const
{
   return column_width;
}


void FontCharacterAtlasBuilder::todo()
{
   // prevent setting font_bin after init
   return;
}

std::pair<AllegroFlare::Vec2D, AllegroFlare::Vec2D> FontCharacterAtlasBuilder::get_uv_for_index(uint32_t unicode_index)
{
   int index = unicode_index - UNICODE_RANGE_START;

   int table_y = 0;
   int table_x = 0;
   int num_columns = 32;

   //int row_height = 112;
   //int column_width = 54;
   //int font_descent = infer_font_descent();

   int num_rows = row_height*256/num_columns;

   int column = index % num_columns;
   int row = index / num_columns;

   return std::pair<AllegroFlare::Vec2D, AllegroFlare::Vec2D>(
      AllegroFlare::Vec2D(column * column_width, row * row_height),
      AllegroFlare::Vec2D((column+1) * column_width, (row+1) * row_height)
   );
}

int FontCharacterAtlasBuilder::infer_font_descent()
{
   return al_get_font_descent(obtain_unicode_font());
}

ALLEGRO_BITMAP* FontCharacterAtlasBuilder::create()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MusicMesh::FontCharacterAtlasBuilder::create]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MusicMesh::FontCharacterAtlasBuilder::create]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MusicMesh::FontCharacterAtlasBuilder::create]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MusicMesh::FontCharacterAtlasBuilder::create]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   //ALLEGRO_FONT *font = obtain_font();
   //int char_width = al_get_text_width(font, "W");
   //int char_height = al_get_font_line_height(font);


   int table_y = 0;
   int table_x = 0;
   int line = 0;
   int num_columns = 32;

   //int row_height = 112;
   //int column_width = 54;

   int num_rows = row_height*256/num_columns;

   ALLEGRO_BITMAP* bitmap = al_create_bitmap(column_width * num_columns, 896); // TODO fix whyrow_height * num_rows);





   bool show_frame = false;
   bool show_hex_number = false;
   bool show_int_number = false;






   ALLEGRO_STATE previous_target_bitmap_state;
   al_store_state(&previous_target_bitmap_state, ALLEGRO_STATE_TARGET_BITMAP);
   al_set_target_bitmap(bitmap);

   uint32_t unicode_range_start = 0x1D100;


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


   int column = 0;
   for (uint32_t character=unicode_range_start; character<=unicode_range_end; character++)
   {
      int x = table_x + column*column_width;
      int y = table_y + line*row_height;
      float column_middle_int = (int)(x + column_width*0.5);

      if (show_frame) al_draw_rectangle(x, y, x+column_width, y+row_height, ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2}, 1.0);

      draw_unicode_character(unicode_font, white, character, ALLEGRO_ALIGN_LEFT, x, y);

      if (show_hex_number)
      {
         // draw hex number
         al_draw_text(
            ui_font_mini,
            white,
            column_middle_int,
            y+row_height-ui_font_mini_line_height - 4,
            ALLEGRO_ALIGN_CENTER,
            as_hex(character).c_str()
         );
      }

      if (show_int_number)
      {
         // draw int number
         al_draw_text(
            ui_font_mini,
            white,
            column_middle_int,
            y+row_height-(ui_font_mini_line_height*2) - 4,
            ALLEGRO_ALIGN_CENTER,
            as_int(character).c_str()
         );
      }

      column += 1;
      if (column >= num_columns) { column = 0; line++; }
   }



   al_restore_state(&previous_target_bitmap_state);


   //for (
   //type: ALLERO_BITMAP*
   //init_with: nullptr
   //getter: true
   return bitmap;
}

void FontCharacterAtlasBuilder::draw_unicode_character(ALLEGRO_FONT* font, ALLEGRO_COLOR color, uint32_t icon, int flags, float x, float y)
{
   static ALLEGRO_USTR *ustr = NULL;
   if (!ustr) ustr = al_ustr_new("");
   al_ustr_set_chr(ustr, 0, icon);
   al_draw_ustr(font, color, x, y, flags, ustr);
   return;
}

ALLEGRO_FONT* FontCharacterAtlasBuilder::obtain_unicode_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MusicMesh::FontCharacterAtlasBuilder::obtain_unicode_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MusicMesh::FontCharacterAtlasBuilder::obtain_unicode_font]: error: guard \"font_bin\" not met");
   }
   std::stringstream font_identifier_and_size;
   font_identifier_and_size << font_identifier << " " << font_size;
   return font_bin->auto_get(font_identifier_and_size.str().c_str());
}

ALLEGRO_FONT* FontCharacterAtlasBuilder::obtain_ui_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MusicMesh::FontCharacterAtlasBuilder::obtain_ui_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MusicMesh::FontCharacterAtlasBuilder::obtain_ui_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Regular.ttf 20");
}

ALLEGRO_FONT* FontCharacterAtlasBuilder::obtain_ui_font_mini()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MusicMesh::FontCharacterAtlasBuilder::obtain_ui_font_mini]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MusicMesh::FontCharacterAtlasBuilder::obtain_ui_font_mini]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Regular.ttf 10");
}

std::string FontCharacterAtlasBuilder::as_hex(uint32_t value, int zero_fill_width)
{
   std::stringstream ss;
   ss << "0x" << std::uppercase << std::setfill('0') << std::setw(zero_fill_width) << std::hex << value;
   return ss.str();
}

std::string FontCharacterAtlasBuilder::as_int(uint32_t value)
{
   std::stringstream ss;
   ss << value;
   return ss.str();
}


} // namespace MusicMesh
} // namespace AllegroFlare


