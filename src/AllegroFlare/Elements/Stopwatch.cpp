

#include <AllegroFlare/Elements/Stopwatch.hpp>

#include <AllegroFlare/TimerFormatter.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


Stopwatch::Stopwatch(AllegroFlare::FontBin* font_bin, AllegroFlare::Timer* timer, std::string font_identifier, int font_size, ALLEGRO_COLOR color)
   : AllegroFlare::Elements::Base()
   , font_bin(font_bin)
   , timer(timer)
   , font_identifier(font_identifier)
   , font_size(font_size)
   , color(color)
{
}


Stopwatch::~Stopwatch()
{
}


void Stopwatch::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void Stopwatch::set_timer(AllegroFlare::Timer* timer)
{
   this->timer = timer;
}


void Stopwatch::set_font_identifier(std::string font_identifier)
{
   this->font_identifier = font_identifier;
}


void Stopwatch::set_font_size(int font_size)
{
   this->font_size = font_size;
}


void Stopwatch::set_color(ALLEGRO_COLOR color)
{
   this->color = color;
}


AllegroFlare::FontBin* Stopwatch::get_font_bin() const
{
   return font_bin;
}


AllegroFlare::Timer* Stopwatch::get_timer() const
{
   return timer;
}


std::string Stopwatch::get_font_identifier() const
{
   return font_identifier;
}


int Stopwatch::get_font_size() const
{
   return font_size;
}


ALLEGRO_COLOR Stopwatch::get_color() const
{
   return color;
}


void Stopwatch::fit_placement_width_and_height_to_stopwatch()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Stopwatch::fit_placement_width_and_height_to_stopwatch]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Stopwatch::fit_placement_width_and_height_to_stopwatch]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Stopwatch::fit_placement_width_and_height_to_stopwatch]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Stopwatch::fit_placement_width_and_height_to_stopwatch]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Stopwatch::fit_placement_width_and_height_to_stopwatch]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Stopwatch::fit_placement_width_and_height_to_stopwatch]: error: guard \"font_bin\" not met");
   }
   std::string ellapsed_time_str = build_ellapsed_time_str();
   float width = al_get_text_width(obtain_font(), ellapsed_time_str.c_str());
   float height = al_get_font_line_height(obtain_font());
   get_placement_ref().size.x = width;
   get_placement_ref().size.y = height;
   return;
}

void Stopwatch::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Stopwatch::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Stopwatch::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Stopwatch::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Stopwatch::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Stopwatch::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Stopwatch::render]: error: guard \"font_bin\" not met");
   }
   ALLEGRO_FONT *font = obtain_font();
   std::string ellapsed_time_str = build_ellapsed_time_str();

   get_placement_ref().start_transform();
   al_draw_text(font, color, 0, 0, ALLEGRO_ALIGN_LEFT, ellapsed_time_str.c_str());
   get_placement_ref().restore_transform();
   return;
}

std::string Stopwatch::build_ellapsed_time_str()
{
   if (!(timer))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Stopwatch::build_ellapsed_time_str]: error: guard \"timer\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Stopwatch::build_ellapsed_time_str]: error: guard \"timer\" not met");
   }
   return AllegroFlare::TimerFormatter(timer->get_elapsed_time_milliseconds()).format();
}

ALLEGRO_FONT* Stopwatch::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Stopwatch::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Stopwatch::obtain_font]: error: guard \"font_bin\" not met");
   }
   std::stringstream result_font_identifier;
   result_font_identifier << font_identifier << " " << font_size;
   return font_bin->auto_get(result_font_identifier.str());
}


} // namespace Elements
} // namespace AllegroFlare


