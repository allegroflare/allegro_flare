

#include <AllegroFlare/Prototypes/FixedRoom2D/Cursor.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


Cursor::Cursor(AllegroFlare::FontBin* font_bin)
   : font_bin(font_bin)
   , x(1920/2)
   , y(1080/2)
   , icon_offset_placement(-9, -2, 0, 0)
   , info_text_offset_placement(40, 0, 0, 0)
   , info_text("[unset-info_text]")
   , info_text_flags(0)
   , icon_character_num(62042)
   , cursor_last_set_at(0)
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


float Cursor::get_x() const
{
   return x;
}


float Cursor::get_y() const
{
   return y;
}


std::string Cursor::get_info_text() const
{
   return info_text;
}


void Cursor::draw()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::Cursor::draw]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::Cursor::draw]: error: guard \"font_bin\" not met");
   }
   AllegroFlare::Placement2D placement(x, y, 0, 0);
   placement.start_transform();

   icon_offset_placement.start_transform();
   draw_cursor();
   icon_offset_placement.restore_transform();

   info_text_offset_placement.start_transform();
   draw_info_text();
   info_text_offset_placement.restore_transform();

   placement.restore_transform();
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

bool Cursor::clamp(float min_x, float min_y, float max_x, float max_y)
{
   if (!((min_x <= max_x)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::Cursor::clamp]: error: guard \"(min_x <= max_x)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::Cursor::clamp]: error: guard \"(min_x <= max_x)\" not met");
   }
   if (!((min_y <= max_y)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::Cursor::clamp]: error: guard \"(min_y <= max_y)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::Cursor::clamp]: error: guard \"(min_y <= max_y)\" not met");
   }
   float began_at_x = x;
   float began_at_y = y;
   float clamped_at_x = std::clamp(x, min_x, max_x);
   float clamped_at_y = std::clamp(y, min_y, max_y);

   x = clamped_at_x;
   y = clamped_at_y;

   if (began_at_x != clamped_at_x) return true;
   if (began_at_y != clamped_at_y) return true;

   return false;
}

void Cursor::move_to(float x, float y)
{
   this->x = x;
   this->y = y;
   return;
}

void Cursor::clear_info_text()
{
   cursor_last_set_at = 0;
   info_text.clear();
   return;
}

void Cursor::set_cursor_to_pointer()
{
   cursor_last_set_at = 0;
   icon_character_num = 62042;
   icon_offset_placement = Placement2D(-9, -2, 0, 0);
   return;
}

void Cursor::set_cursor_to_grab()
{
   cursor_last_set_at = 0;
   icon_character_num = 62038;
   icon_offset_placement = Placement2D(-16, -4, 0, 0);
   return;
}

void Cursor::draw_unicode_character(ALLEGRO_FONT* font, ALLEGRO_COLOR color, uint32_t icon, int flags)
{
   static ALLEGRO_USTR *ustr = NULL;
   if (!ustr) ustr = al_ustr_new("");
   al_ustr_set_chr(ustr, 0, icon);
   al_draw_ustr(font, color, 0, 0, flags, ustr);
   return;
}

ALLEGRO_FONT* Cursor::obtain_cursor_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::Cursor::obtain_cursor_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::Cursor::obtain_cursor_font]: error: guard \"font_bin\" not met");
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
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::Cursor::obtain_info_text_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::Cursor::obtain_info_text_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Regular.ttf 20");
}

void Cursor::draw_cursor()
{
   ALLEGRO_FONT *cursor_font = obtain_cursor_font();
   draw_unicode_character(cursor_font, ALLEGRO_COLOR{1, 1, 1, 1}, icon_character_num, 0);
   return;
}

void Cursor::draw_info_text()
{
   ALLEGRO_FONT* info_text_font = obtain_info_text_font();
   al_draw_text(info_text_font, ALLEGRO_COLOR{1, 1, 1, 1}, 0, 0, info_text_flags, info_text.c_str());
   return;
}


} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


