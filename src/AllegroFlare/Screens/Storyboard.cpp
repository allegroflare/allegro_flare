

#include <AllegroFlare/Screens/Storyboard.hpp>
#include <allegro5/allegro_font.h>
#include <AllegroFlare/Color.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Screens
{


Storyboard::Storyboard(AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter, std::vector<std::string> pages, std::string screen_identifier_to_switch_to_after_completing, intptr_t current_page_num)
   : AllegroFlare::Screens::Base()
   , font_bin(font_bin)
   , event_emitter(event_emitter)
   , pages(pages)
   , screen_identifier_to_switch_to_after_completing(screen_identifier_to_switch_to_after_completing)
   , current_page_num(current_page_num)
{
}


Storyboard::~Storyboard()
{
}


intptr_t Storyboard::get_current_page_num()
{
   return current_page_num;
}


void Storyboard::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "Storyboard" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "Storyboard" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   ALLEGRO_FONT *text_font = obtain_font();

   al_clear_to_color(AllegroFlare::Color::Black);

   if (current_page_num >= pages.size()) return;

   float x_padding = 150;
   float y_padding = 150;

   al_draw_multiline_text(
         text_font,
         AllegroFlare::Color(0xd0f2c5).to_al(),
         x_padding,
         y_padding,
         1920 - x_padding*2,
         al_get_font_line_height(text_font)*1.75,
         0,
         pages[current_page_num].c_str()
      );
   return;
}

void Storyboard::reset()
{
   current_page_num = 0;
   return;
}

void Storyboard::on_activate()
{
   reset();
   return;
}

void Storyboard::primary_timer_func()
{
   render();
   return;
}

void Storyboard::key_down_func(ALLEGRO_EVENT* event)
{
   if (!(event_emitter))
      {
         std::stringstream error_message;
         error_message << "Storyboard" << "::" << "key_down_func" << ": error: " << "guard \"event_emitter\" not met";
         throw std::runtime_error(error_message.str());
      }
   current_page_num++;

   if (current_page_num >= pages.size())
      event_emitter->emit_switch_screen_event(screen_identifier_to_switch_to_after_completing);

   return;
}

ALLEGRO_FONT* Storyboard::obtain_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Storyboard" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("DroidSans.ttf -72");
}
} // namespace Screens
} // namespace AllegroFlare


