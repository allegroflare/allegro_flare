

#include <AllegroFlare/Screens/Basic.hpp>

#include <iostream>
#include <allegro5/allegro_color.h>
#include <AllegroFlare/ConsoleColor.hpp>
#include <AllegroFlare/Display.hpp>


namespace AllegroFlare
{
namespace Screens
{


Basic::Basic(std::string type)
   : AllegroFlare::ElementID(nullptr)
   , type(type)
   , active(true)
{
}


Basic::~Basic()
{
}


void Basic::set_type(std::string type)
{
   this->type = type;
}


std::string Basic::get_type()
{
   return type;
}


bool Basic::is_type(std::string possible_type)
{
   return type == possible_type;
}


bool Basic::is_active()
{
   return this->active;
}


void Basic::on_event(ALLEGRO_EVENT *ev) {}
void Basic::primary_timer_func() {}
void Basic::timer_func() {}
void Basic::mouse_axes_func() {}
void Basic::mouse_warp_func() {}
void Basic::display_switch_in_func() {}
void Basic::display_switch_out_func() {}
void Basic::mouse_down_func() {}
void Basic::mouse_up_func() {}
void Basic::key_down_func(ALLEGRO_EVENT *ev) {}
void Basic::key_up_func(ALLEGRO_EVENT *ev) {}
void Basic::key_char_func(ALLEGRO_EVENT *ev) {}
void Basic::joy_button_down_func(ALLEGRO_EVENT *ev) {}
void Basic::joy_button_up_func(ALLEGRO_EVENT *ev) {}
void Basic::joy_axis_func(ALLEGRO_EVENT *ev) {}
void Basic::joy_config_func(ALLEGRO_EVENT *ev) {}
void Basic::user_event_func(ALLEGRO_EVENT *ev) {}
void Basic::event_emitter_event_func(ALLEGRO_EVENT *ev) {}
void Basic::virtual_control_button_up_func(ALLEGRO_EVENT *ev) {};
void Basic::virtual_control_button_down_func(ALLEGRO_EVENT *ev) {};
void Basic::virtual_control_axis_change_func(ALLEGRO_EVENT *ev) {};
void Basic::native_menu_click_func() {}


} // namespace Screens
} // namespace AllegroFlare


