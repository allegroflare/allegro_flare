

#include <AllegroFlare/Screens/StoryboardPlayer.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/VirtualControls.hpp>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Screens
{


StoryboardPlayer::StoryboardPlayer(AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter, std::string game_event_name_to_emit_after_completing)
   : AllegroFlare::Screens::Base("StoryboardPlayer")
   , font_bin(font_bin)
   , event_emitter(event_emitter)
   , storyboard_element({})
   , game_event_name_to_emit_after_completing(game_event_name_to_emit_after_completing)
   , initialized(false)
{
}


StoryboardPlayer::~StoryboardPlayer()
{
}


void StoryboardPlayer::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void StoryboardPlayer::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void StoryboardPlayer::set_game_event_name_to_emit_after_completing(std::string game_event_name_to_emit_after_completing)
{
   this->game_event_name_to_emit_after_completing = game_event_name_to_emit_after_completing;
}


std::string StoryboardPlayer::get_game_event_name_to_emit_after_completing()
{
   return game_event_name_to_emit_after_completing;
}


AllegroFlare::Elements::Storyboard &StoryboardPlayer::get_storyboard_element_ref()
{
   return storyboard_element;
}


void StoryboardPlayer::initialize()
{
   if (!((!initialized)))
      {
         std::stringstream error_message;
         error_message << "StoryboardPlayer" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
         throw std::runtime_error(error_message.str());
      }
   storyboard_element.set_font_bin(font_bin);
   initialized = true;
   return;
}

void StoryboardPlayer::on_activate()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "StoryboardPlayer" << "::" << "on_activate" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   storyboard_element.reset();
   return;
}

void StoryboardPlayer::primary_timer_func()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "StoryboardPlayer" << "::" << "primary_timer_func" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   storyboard_element.update();
   storyboard_element.render();
   return;
}

void StoryboardPlayer::advance()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "StoryboardPlayer" << "::" << "advance" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(event_emitter))
      {
         std::stringstream error_message;
         error_message << "StoryboardPlayer" << "::" << "advance" << ": error: " << "guard \"event_emitter\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (storyboard_element.get_finished()) return;

   storyboard_element.advance();

   if (storyboard_element.get_finished())
   {
      if (!game_event_name_to_emit_after_completing.empty())
      {
         event_emitter->emit_game_event(
            AllegroFlare::GameEvent(game_event_name_to_emit_after_completing)
         );
      }
   }

   return;
}

void StoryboardPlayer::virtual_control_button_down_func(int player_num, int button_num, bool is_repeat)
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "StoryboardPlayer" << "::" << "virtual_control_button_down_func" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(event_emitter))
      {
         std::stringstream error_message;
         error_message << "StoryboardPlayer" << "::" << "virtual_control_button_down_func" << ": error: " << "guard \"event_emitter\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (storyboard_element.get_finished()) return;

   if (button_num == AllegroFlare::VirtualControls::get_BUTTON_A()
     || button_num == AllegroFlare::VirtualControls::get_BUTTON_START()
     || button_num == AllegroFlare::VirtualControls::get_BUTTON_RIGHT())
   {
      advance();
   }

   return;
}
} // namespace Screens
} // namespace AllegroFlare


