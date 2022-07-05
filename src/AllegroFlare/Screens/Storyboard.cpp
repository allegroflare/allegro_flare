

#include <AllegroFlare/Screens/Storyboard.hpp>
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
namespace Screens
{


Storyboard::Storyboard(AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter, std::string game_event_name_to_emit_after_completing)
   : AllegroFlare::Screens::Base("Storyboard")
   , font_bin(font_bin)
   , event_emitter(event_emitter)
   , storyboard_element({})
   , game_event_name_to_emit_after_completing(game_event_name_to_emit_after_completing)
   , initialized(false)
{
}


Storyboard::~Storyboard()
{
}


void Storyboard::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void Storyboard::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void Storyboard::set_game_event_name_to_emit_after_completing(std::string game_event_name_to_emit_after_completing)
{
   this->game_event_name_to_emit_after_completing = game_event_name_to_emit_after_completing;
}


std::string Storyboard::get_game_event_name_to_emit_after_completing()
{
   return game_event_name_to_emit_after_completing;
}


AllegroFlare::Elements::Storyboard &Storyboard::get_storyboard_element_ref()
{
   return storyboard_element;
}


void Storyboard::initialize()
{
   if (!((!initialized)))
      {
         std::stringstream error_message;
         error_message << "Storyboard" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
         throw std::runtime_error(error_message.str());
      }
   storyboard_element.set_font_bin(font_bin);
   initialized = true;
   return;
}

void Storyboard::on_activate()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Storyboard" << "::" << "on_activate" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   storyboard_element.reset();
   return;
}

void Storyboard::primary_timer_func()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Storyboard" << "::" << "primary_timer_func" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   storyboard_element.render();
   return;
}

void Storyboard::key_down_func(ALLEGRO_EVENT* event)
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Storyboard" << "::" << "key_down_func" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(event_emitter))
      {
         std::stringstream error_message;
         error_message << "Storyboard" << "::" << "key_down_func" << ": error: " << "guard \"event_emitter\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (storyboard_element.get_finished()) return;

   storyboard_element.advance_page();

   if (storyboard_element.get_finished())
   {
      if (!game_event_name_to_emit_after_completing.empty())
      {
         event_emitter->emit_game_event(AllegroFlare::GameEvent("storyboard_finished"));
      }
   }

   return;
}
} // namespace Screens
} // namespace AllegroFlare


