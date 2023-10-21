

#include <AllegroFlare/Screens/Base.hpp>

#include <iostream>
#include <allegro5/allegro_color.h>
#include <AllegroFlare/ConsoleColor.hpp>
#include <AllegroFlare/Display.hpp>


namespace AllegroFlare
{
namespace Screens
{


Base::Base(std::string type)
   : type(type)
{
}


Base::~Base()
{
}


void Base::set_type(std::string type)
{
   this->type = type;
}


std::string Base::get_type()
{
   return type;
}


bool Base::is_type(std::string possible_type)
{
   return type == possible_type;
}


void Base::on_activate() {}
void Base::on_deactivate() {}
void Base::on_event(ALLEGRO_EVENT *ev) {}
void Base::primary_timer_func() {}
void Base::timer_func() {}
void Base::mouse_axes_func(ALLEGRO_EVENT *ev) {}
void Base::mouse_warp_func(ALLEGRO_EVENT *ev) {}
void Base::display_switch_in_func() {}
void Base::display_switch_out_func() {}
void Base::mouse_down_func(ALLEGRO_EVENT *ev) {}
void Base::mouse_up_func(ALLEGRO_EVENT *ev) {}
void Base::key_down_func(ALLEGRO_EVENT *ev) {}
void Base::key_up_func(ALLEGRO_EVENT *ev) {}
void Base::key_char_func(ALLEGRO_EVENT *ev) {}
void Base::joy_button_down_func(ALLEGRO_EVENT *ev) {}
void Base::joy_button_up_func(ALLEGRO_EVENT *ev) {}
void Base::joy_axis_func(ALLEGRO_EVENT *ev) {}
void Base::joy_config_func(ALLEGRO_EVENT *ev) {}
void Base::user_event_func(ALLEGRO_EVENT *ev) {}
void Base::event_emitter_event_func(ALLEGRO_EVENT *ev) {}
void Base::game_event_func(AllegroFlare::GameEvent *game_event) {}
void Base::virtual_control_button_up_func(
      AllegroFlare::Player* player,
      AllegroFlare::VirtualControllers::Base* virtual_controller,
      int virtual_controller_button_num,
      bool is_repeat
) {}
void Base::virtual_control_button_down_func(
      AllegroFlare::Player* player,
      AllegroFlare::VirtualControllers::Base* virtual_controller,
      int virtual_controller_button_num,
      bool is_repeat
) {}
void Base::virtual_control_axis_change_func(ALLEGRO_EVENT *ev) {};
void Base::native_menu_click_func() {}


} // namespace Screens
} // namespace AllegroFlare


