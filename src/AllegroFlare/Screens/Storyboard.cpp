

#include <AllegroFlare/Screens/Storyboard.hpp>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{


Storyboard::Storyboard(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::FontBin* font_bin, std::string game_event_name_to_emit_after_completing, uint32_t route_event_to_emit_after_completing)
   : AllegroFlare::Screens::Base("Storyboard")
   , event_emitter(event_emitter)
   , font_bin(font_bin)
   , storyboard_element({})
   , on_finished_callback_func()
   , on_finished_callback_func_user_data(nullptr)
   , auto_advance(false)
   , game_event_name_to_emit_after_completing(game_event_name_to_emit_after_completing)
   , route_event_to_emit_after_completing(route_event_to_emit_after_completing)
   , initialized(false)
{
}


Storyboard::~Storyboard()
{
}


void Storyboard::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void Storyboard::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void Storyboard::set_on_finished_callback_func(std::function<void(AllegroFlare::Screens::Storyboard*, void*)> on_finished_callback_func)
{
   this->on_finished_callback_func = on_finished_callback_func;
}


void Storyboard::set_on_finished_callback_func_user_data(void* on_finished_callback_func_user_data)
{
   this->on_finished_callback_func_user_data = on_finished_callback_func_user_data;
}


void Storyboard::set_auto_advance(bool auto_advance)
{
   this->auto_advance = auto_advance;
}


void Storyboard::set_game_event_name_to_emit_after_completing(std::string game_event_name_to_emit_after_completing)
{
   this->game_event_name_to_emit_after_completing = game_event_name_to_emit_after_completing;
}


void Storyboard::set_route_event_to_emit_after_completing(uint32_t route_event_to_emit_after_completing)
{
   this->route_event_to_emit_after_completing = route_event_to_emit_after_completing;
}


std::function<void(AllegroFlare::Screens::Storyboard*, void*)> Storyboard::get_on_finished_callback_func() const
{
   return on_finished_callback_func;
}


void* Storyboard::get_on_finished_callback_func_user_data() const
{
   return on_finished_callback_func_user_data;
}


bool Storyboard::get_auto_advance() const
{
   return auto_advance;
}


std::string Storyboard::get_game_event_name_to_emit_after_completing() const
{
   return game_event_name_to_emit_after_completing;
}


uint32_t Storyboard::get_route_event_to_emit_after_completing() const
{
   return route_event_to_emit_after_completing;
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
      error_message << "[AllegroFlare::Screens::Storyboard::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Storyboard::initialize]: error: guard \"(!initialized)\" not met");
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
      error_message << "[AllegroFlare::Screens::Storyboard::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Storyboard::on_activate]: error: guard \"initialized\" not met");
   }
   storyboard_element.reset();
   if (storyboard_element.infer_has_no_pages())
   {
      AllegroFlare::Logger::info_from(
         "AllegroFlare::Screens::Storyboard",
         "The storyboard is empty (it has no pages). Events, callbacks will now be triggered to indicate the "
            "storyboard is finished (aka completed)."
      );
      emit_completion_event();
   }
   return;
}

void Storyboard::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Storyboard::on_deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Storyboard::on_deactivate]: error: guard \"initialized\" not met");
   }
   return;
}

void Storyboard::primary_timer_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Storyboard::primary_timer_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Storyboard::primary_timer_func]: error: guard \"initialized\" not met");
   }

   storyboard_element.update();
   if (storyboard_element.get_can_advance_to_next_page() && auto_advance) advance();

   storyboard_element.render();
   return;
}

void Storyboard::clear_game_event_name_to_emit_after_completing()
{
   game_event_name_to_emit_after_completing.clear();
   return;
}

void Storyboard::clear_route_event_to_emit_after_completing()
{
   route_event_to_emit_after_completing = 0;
   return;
}

void Storyboard::emit_completion_event()
{
   if (!game_event_name_to_emit_after_completing.empty())
   {
      event_emitter->emit_game_event(AllegroFlare::GameEvent(game_event_name_to_emit_after_completing));
   }
   if (route_event_to_emit_after_completing != 0)
   {
      event_emitter->emit_router_event(route_event_to_emit_after_completing);
   }
   // TODO: Test this callback
   if (on_finished_callback_func) on_finished_callback_func(this, on_finished_callback_func_user_data);
   return;
}

void Storyboard::advance()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Storyboard::advance]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Storyboard::advance]: error: guard \"initialized\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Storyboard::advance]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Storyboard::advance]: error: guard \"event_emitter\" not met");
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
      error_message << "[AllegroFlare::Screens::Storyboard::virtual_control_button_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Storyboard::virtual_control_button_down_func]: error: guard \"initialized\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::Storyboard::virtual_control_button_down_func]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::Storyboard::virtual_control_button_down_func]: error: guard \"event_emitter\" not met");
   }
   if (storyboard_element.get_finished()) return;

   if (!virtual_controller->is_type(AllegroFlare::VirtualControllers::GenericController::TYPE))
   {
      // TODO test this
      AllegroFlare::Logger::throw_error("AllegroFlare/Screens/Storyboard", "Expecting virtual_controller to be of "
                                        "type GenericController::TYPE but it is not.");
   }

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


