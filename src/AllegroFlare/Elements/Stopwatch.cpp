

#include <AllegroFlare/Elements/Stopwatch.hpp>
#include <AllegroFlare/TimerFormatter.hpp>
#include <AllegroFlare/Color.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{


Stopwatch::Stopwatch(AllegroFlare::FontBin* font_bin)
   : AllegroFlare::Elements::Base()
   , font_bin(font_bin)
   , timer({})
{
}


Stopwatch::~Stopwatch()
{
}


void Stopwatch::start()
{
   timer.start();
   return;
}

void Stopwatch::pause()
{
   timer.pause();
   return;
}

void Stopwatch::reset()
{
   timer.reset();
   return;
}

void Stopwatch::is_running()
{
   timer.is_running();
   return;
}

void Stopwatch::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "Stopwatch" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "Stopwatch" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Stopwatch" << "::" << "render" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   ALLEGRO_COLOR color = AllegroFlare::Color::White;
   ALLEGRO_FONT *font = obtain_font();
   std::string ellapsed_time_str = AllegroFlare::TimerFormatter(timer.get_elapsed_time_milliseconds()).format();

   get_placement_ref().start_transform();
   al_draw_text(font, color, 0, 0, ALLEGRO_ALIGN_LEFT, ellapsed_time_str.c_str());
   get_placement_ref().restore_transform();
   return;
}

ALLEGRO_FONT* Stopwatch::obtain_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Stopwatch" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("DroidSans.ttf -74");
}
} // namespace Elements
} // namespace AllegroFlare


