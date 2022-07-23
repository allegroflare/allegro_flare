

#include <AllegroFlare/Prototypes/FixedRoom2D/Cursor.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


Cursor::Cursor(AllegroFlare::FontBin* font_bin)
   : font_bin(font_bin)
   , x(1920/2)
   , y(1920/2)
   , icon_offset_placement({})
   , info_text_offset_placement({})
   , info_text("[unset-info_text]")
   , icon_character_num(62042)
{
}


Cursor::~Cursor()
{
}


void Cursor::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void Cursor::set_x(float x)
{
   this->x = x;
}


void Cursor::set_y(float y)
{
   this->y = y;
}


void Cursor::set_info_text(std::string info_text)
{
   this->info_text = info_text;
}


float Cursor::get_x()
{
   return x;
}


float Cursor::get_y()
{
   return y;
}


std::string Cursor::get_info_text()
{
   return info_text;
}


void Cursor::draw()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Cursor" << "::" << "draw" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   icon_offset_placement.start_transform();
   draw_cursor();
   icon_offset_placement.restore_transform();

   info_text_offset_placement.start_transform();
   draw_info_text();
   info_text_offset_placement.restore_transform();
   return;
}

void Cursor::update()
{
   // currently empty
   return;
}

void Cursor::move(float distance_x, float distance_y)
{
   x += distance_x;
   y += distance_y;
   return;
}

void Cursor::clear_info_text()
{
   info_text.clear();
   return;
}

void Cursor::set_cursor_to_pointer()
{
   icon_character_num = 62042;
   return;
}

void Cursor::set_cursor_to_grab()
{
   icon_character_num = 62038;
   return;
}

void Cursor::draw_unicode_character(ALLEGRO_FONT* font, ALLEGRO_COLOR color, uint32_t icon, float x, float y, int flags)
{
   static ALLEGRO_USTR *ustr = NULL;
   if (!ustr) ustr = al_ustr_new("");
   al_ustr_set_chr(ustr, 0, icon);
   al_draw_ustr(font, color, x, y, flags, ustr);
   return;
}

ALLEGRO_FONT* Cursor::obtain_cursor_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Cursor" << "::" << "obtain_cursor_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::string font_name = "fa-solid-900.ttf";
   int cursor_font_size = 30;

   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << cursor_font_size;
   return font_bin->auto_get(composite_font_str.str());
}

ALLEGRO_FONT* Cursor::obtain_info_text_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Cursor" << "::" << "obtain_info_text_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("Inter-Medium.ttf 20");
}

void Cursor::draw_cursor()
{
   ALLEGRO_FONT *cursor_font = obtain_cursor_font();
   draw_unicode_character(cursor_font, ALLEGRO_COLOR{1, 1, 1, 1}, icon_character_num, x, y, 0);
   return;
}

void Cursor::draw_info_text()
{
   ALLEGRO_FONT* info_text_font = obtain_info_text_font();
   al_draw_text(info_text_font, ALLEGRO_COLOR{1, 1, 1, 1}, 0, 0, 0, info_text.c_str());
   return;
}
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


