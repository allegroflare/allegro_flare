

#include <AllegroFlare/Screens/RollingCredits.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{


RollingCredits::RollingCredits(AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter, AllegroFlare::Elements::RollingCredits::RollingCredits rolling_credits_component, float surface_width, float surface_height, std::string game_event_name_to_emit_after_completing, uint32_t route_event_to_emit_after_completing)
   : AllegroFlare::Screens::Base("RollingCredits")
   , font_bin(font_bin)
   , event_emitter(event_emitter)
   , rolling_credits_component(rolling_credits_component)
   , surface_width(surface_width)
   , surface_height(surface_height)
   , y_offset(0.0f)
   , y_speed(2.0f)
   , on_finished_callback_func()
   , on_finished_callback_func_user_data(nullptr)
   , cached_calculated_height(0.0f)
   , game_event_name_to_emit_after_completing(game_event_name_to_emit_after_completing)
   , route_event_to_emit_after_completing(route_event_to_emit_after_completing)
   , scroll_is_past_end(false)
   , initialized(false)
{
}


RollingCredits::~RollingCredits()
{
}


void RollingCredits::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void RollingCredits::set_surface_width(float surface_width)
{
   this->surface_width = surface_width;
}


void RollingCredits::set_surface_height(float surface_height)
{
   this->surface_height = surface_height;
}


void RollingCredits::set_y_offset(float y_offset)
{
   this->y_offset = y_offset;
}


void RollingCredits::set_y_speed(float y_speed)
{
   this->y_speed = y_speed;
}


void RollingCredits::set_on_finished_callback_func(std::function<void(AllegroFlare::Screens::RollingCredits*, void*)> on_finished_callback_func)
{
   this->on_finished_callback_func = on_finished_callback_func;
}


void RollingCredits::set_on_finished_callback_func_user_data(void* on_finished_callback_func_user_data)
{
   this->on_finished_callback_func_user_data = on_finished_callback_func_user_data;
}


void RollingCredits::set_game_event_name_to_emit_after_completing(std::string game_event_name_to_emit_after_completing)
{
   this->game_event_name_to_emit_after_completing = game_event_name_to_emit_after_completing;
}


void RollingCredits::set_route_event_to_emit_after_completing(uint32_t route_event_to_emit_after_completing)
{
   this->route_event_to_emit_after_completing = route_event_to_emit_after_completing;
}


AllegroFlare::Elements::RollingCredits::RollingCredits RollingCredits::get_rolling_credits_component() const
{
   return rolling_credits_component;
}


float RollingCredits::get_surface_width() const
{
   return surface_width;
}


float RollingCredits::get_surface_height() const
{
   return surface_height;
}


float RollingCredits::get_y_offset() const
{
   return y_offset;
}


float RollingCredits::get_y_speed() const
{
   return y_speed;
}


std::function<void(AllegroFlare::Screens::RollingCredits*, void*)> RollingCredits::get_on_finished_callback_func() const
{
   return on_finished_callback_func;
}


void* RollingCredits::get_on_finished_callback_func_user_data() const
{
   return on_finished_callback_func_user_data;
}


float RollingCredits::get_cached_calculated_height() const
{
   return cached_calculated_height;
}


std::string RollingCredits::get_game_event_name_to_emit_after_completing() const
{
   return game_event_name_to_emit_after_completing;
}


uint32_t RollingCredits::get_route_event_to_emit_after_completing() const
{
   return route_event_to_emit_after_completing;
}


bool RollingCredits::get_scroll_is_past_end() const
{
   return scroll_is_past_end;
}


AllegroFlare::Elements::RollingCredits::RollingCredits &RollingCredits::get_rolling_credits_component_ref()
{
   return rolling_credits_component;
}


float &RollingCredits::get_y_offset_ref()
{
   return y_offset;
}


float &RollingCredits::get_y_speed_ref()
{
   return y_speed;
}


void RollingCredits::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::RollingCredits::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::RollingCredits::on_activate]: error: guard \"initialized\" not met");
   }
   y_offset = -surface_height;
   scroll_is_past_end = false;
   return;
}

void RollingCredits::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::RollingCredits::on_deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::RollingCredits::on_deactivate]: error: guard \"initialized\" not met");
   }
   return;
}

void RollingCredits::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::RollingCredits::set_font_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::RollingCredits::set_font_bin]: error: guard \"(!initialized)\" not met");
   }
   this->font_bin = font_bin;
   return;
}

void RollingCredits::set_sections(std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> sections)
{
   // TODO: Test this method
   rolling_credits_component.set_sections(sections);
   // TODO: Confirm this re-calculation of height is appropriate here
   // TODO: Test this calculated height recalculation occurs
   if (initialized) cached_calculated_height = rolling_credits_component.calculate_height();
   return;
}

void RollingCredits::append_section(AllegroFlare::Elements::RollingCredits::Sections::Base* section_to_append)
{
   if (!(section_to_append))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::RollingCredits::append_section]: error: guard \"section_to_append\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::RollingCredits::append_section]: error: guard \"section_to_append\" not met");
   }
   // TODO: Test this method
   rolling_credits_component.append_section(section_to_append);
   // TODO: Confirm this re-calculation of height is appropriate here
   // TODO: Test this calculated height recalculation occurs
   if (initialized) cached_calculated_height = rolling_credits_component.calculate_height();
   return;
}

void RollingCredits::append_sections(std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> sections)
{
   rolling_credits_component.append_sections(sections);
   // TODO: Confirm this re-calculation of height is appropriate here
   // TODO: Test this calculated height recalculation occurs
   if (initialized) cached_calculated_height = rolling_credits_component.calculate_height();
   return;
}

void RollingCredits::clear_game_event_name_to_emit_after_completing()
{
   game_event_name_to_emit_after_completing.clear();
   return;
}

void RollingCredits::clear_route_event_to_emit_after_completing()
{
   route_event_to_emit_after_completing = 0;
   return;
}

void RollingCredits::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::RollingCredits::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::RollingCredits::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::RollingCredits::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::RollingCredits::initialize]: error: guard \"font_bin\" not met");
   }
   rolling_credits_component.set_surface_height(surface_height);
   rolling_credits_component.set_surface_width(surface_width);
   rolling_credits_component.set_font_bin(font_bin);
   rolling_credits_component.initialize();
   //rolling_credits_component.set_y_offset(y_offset);
   cached_calculated_height = rolling_credits_component.calculate_height();
   initialized = true;
   return;
}

void RollingCredits::update()
{
   if (scroll_is_past_end) return;

   y_offset += y_speed;
   if (y_offset > cached_calculated_height)
   {
      scroll_is_past_end = true;
      emit_completion_event();
   }
   return;
}

void RollingCredits::emit_completion_event()
{
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::RollingCredits::emit_completion_event]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::RollingCredits::emit_completion_event]: error: guard \"event_emitter\" not met");
   }
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

void RollingCredits::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::RollingCredits::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::RollingCredits::render]: error: guard \"al_is_system_installed()\" not met");
   }
   rolling_credits_component.set_y_offset(-y_offset);
   rolling_credits_component.render();
   return;
}

void RollingCredits::primary_timer_func()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::RollingCredits::primary_timer_func]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::RollingCredits::primary_timer_func]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::RollingCredits::primary_timer_func]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::RollingCredits::primary_timer_func]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   update();
   render();
   return;
}


} // namespace Screens
} // namespace AllegroFlare


