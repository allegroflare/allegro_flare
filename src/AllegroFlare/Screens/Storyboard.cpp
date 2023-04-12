

#include <AllegroFlare/Screens/Storyboard.hpp>

#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{


Storyboard::Storyboard(AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter, std::string game_event_name_to_emit_after_completing)
   : AllegroFlare::Screens::Base("Storyboard")
   , font_bin(font_bin)
   , event_emitter(event_emitter)
   , storyboard_element({})
   , auto_advance(false)
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


void Storyboard::set_auto_advance(bool auto_advance)
{
   this->auto_advance = auto_advance;
}


void Storyboard::set_game_event_name_to_emit_after_completing(std::string game_event_name_to_emit_after_completing)
{
   this->game_event_name_to_emit_after_completing = game_event_name_to_emit_after_completing;
}


bool Storyboard::get_auto_advance() const
{
   return auto_advance;
}


std::string Storyboard::get_game_event_name_to_emit_after_completing() const
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
      error_message << "[Storyboard::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Storyboard::initialize: error: guard \"(!initialized)\" not met");
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
      error_message << "[Storyboard::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Storyboard::on_activate: error: guard \"initialized\" not met");
   }
   storyboard_element.reset();
   return;
}

void Storyboard::primary_timer_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Storyboard::primary_timer_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Storyboard::primary_timer_func: error: guard \"initialized\" not met");
   }
   storyboard_element.update();
   if (storyboard_element.get_can_advance_to_next_page() && auto_advance) advance();

   storyboard_element.render();
   return;
}

void Storyboard::emit_completion_event()
{
   if (!game_event_name_to_emit_after_completing.empty())
   {
      event_emitter->emit_game_event(AllegroFlare::GameEvent(game_event_name_to_emit_after_completing));
   }
   return;
}

void Storyboard::advance()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Storyboard::advance]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Storyboard::advance: error: guard \"initialized\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[Storyboard::advance]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Storyboard::advance: error: guard \"event_emitter\" not met");
   }
   if (storyboard_element.get_finished()) return;

   storyboard_element.advance();

   if (storyboard_element.get_finished())
   {
      emit_completion_event();
   }

   return;
}

void Storyboard::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Storyboard::virtual_control_button_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Storyboard::virtual_control_button_down_func: error: guard \"initialized\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[Storyboard::virtual_control_button_down_func]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Storyboard::virtual_control_button_down_func: error: guard \"event_emitter\" not met");
   }
   if (storyboard_element.get_finished()) return;

   // TODO: validate controller type

   if (virtual_controller_button_num == AllegroFlare::VirtualControllers::GenericController::BUTTON_A
     || virtual_controller_button_num == AllegroFlare::VirtualControllers::GenericController::BUTTON_MENU
     || virtual_controller_button_num == AllegroFlare::VirtualControllers::GenericController::BUTTON_RIGHT)
   {
      advance();
   }

   return;
}


} // namespace Screens
} // namespace AllegroFlare


