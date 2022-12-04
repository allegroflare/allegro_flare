

#include <AllegroFlare/Elements/Stopwatch.hpp>

#include <AllegroFlare/TimerFormatter.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


Stopwatch::Stopwatch(AllegroFlare::FontBin* font_bin, AllegroFlare::Timer* timer)
   : AllegroFlare::Elements::Base()
   , font_bin(font_bin)
   , timer(timer)
   , color(ALLEGRO_COLOR{1, 1, 1, 1})
{
}


Stopwatch::~Stopwatch()
{
}


void Stopwatch::set_timer(AllegroFlare::Timer* timer)
{
   this->timer = timer;
}


void Stopwatch::set_color(ALLEGRO_COLOR color)
{
   this->color = color;
}


AllegroFlare::Timer* Stopwatch::get_timer() const
{
   return timer;
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
      error_message << "[Stopwatch::fit_placement_width_and_height_to_stopwatch]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stopwatch::fit_placement_width_and_height_to_stopwatch: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Stopwatch::fit_placement_width_and_height_to_stopwatch]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stopwatch::fit_placement_width_and_height_to_stopwatch: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Stopwatch::fit_placement_width_and_height_to_stopwatch]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stopwatch::fit_placement_width_and_height_to_stopwatch: error: guard \"font_bin\" not met");
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
      error_message << "[Stopwatch::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stopwatch::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Stopwatch::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stopwatch::render: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Stopwatch::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stopwatch::render: error: guard \"font_bin\" not met");
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
      error_message << "[Stopwatch::build_ellapsed_time_str]: error: guard \"timer\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stopwatch::build_ellapsed_time_str: error: guard \"timer\" not met");
   }
   return AllegroFlare::TimerFormatter(timer->get_elapsed_time_milliseconds()).format();
}

ALLEGRO_FONT* Stopwatch::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Stopwatch::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stopwatch::obtain_font: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Medium.ttf -74");
}


} // namespace Elements
} // namespace AllegroFlare


