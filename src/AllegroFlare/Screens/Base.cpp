

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
   , background(nullptr)
   , foreground(nullptr)
   , update_strategy(AllegroFlare::Screens::Base::UpdateStrategy::LEGACY_SINGLE_PRIMARY_TIMER_FUNC)
{
}


Base::~Base()
{
}


//void Base::set_type(std::string type)
//{
   //this->type = type;
//}
void Base::destroy() {}


std::string Base::get_type()
{
   return type;
}


bool Base::is_type(std::string possible_type)
{
   return type == possible_type;
}


void Base::set_update_strategy(UpdateStrategy update_strategy)
{
   this->update_strategy = update_strategy;
}


bool Base::is_using_update_strategy(UpdateStrategy possible_update_strategy)
{
   return (this->update_strategy == possible_update_strategy);
}


void Base::set_background(AllegroFlare::Elements::Backgrounds::Base *background)
{
   this->background = background;
}


void Base::set_foreground(AllegroFlare::Elements::Backgrounds::Base *foreground)
{
   this->foreground = foreground;
}


AllegroFlare::Elements::Backgrounds::Base *Base::get_background()
{
   return background;
}


AllegroFlare::Elements::Backgrounds::Base *Base::get_foreground()
{
   return foreground;
}


void Base::managed_primary_time_step_func(double time_step_increment, double world_time_after_step)
{
   // TODO
}


void Base::managed_primary_update_func(double time_now, double delta_time)
{
   if (!is_using_update_strategy(UpdateStrategy::SEPARATE_UPDATE_AND_RENDER_FUNCS))
   {
      // TODO: Improve this error message
      throw std::runtime_error(
         "Cannot call this function unless using SEPARATE_UPDATE_AND_RENDER_FUNCS update strategy"
      );
   }

   if (background) background->update(); // TODO: Pass in delta_time
   primary_update_func(time_now, delta_time);
   if (foreground) foreground->update(); // TODO: Pass in delta_time
}


void Base::managed_primary_render_func()
{
   if (!is_using_update_strategy(UpdateStrategy::SEPARATE_UPDATE_AND_RENDER_FUNCS))
   {
      // TODO: Improve this error message
      throw std::runtime_error(
         "Cannot call this function unless using SEPARATE_UPDATE_AND_RENDER_FUNCS update strategy"
      );
   }

   if (background) background->render();
   primary_render_func();
   if (foreground) foreground->render();
}


void Base::managed_primary_timer_func()
{
   if (!is_using_update_strategy(UpdateStrategy::LEGACY_SINGLE_PRIMARY_TIMER_FUNC))
   {
      // TODO: Improve this error message
      throw std::runtime_error(
         "Cannot call this function unless using LEGACY_SINGLE_PRIMARY_TIMER_FUNC update strategy"
      );
   }

   if (background)
   {
      background->update();
      background->render();
   }
   primary_timer_func();
   if (foreground)
   {
      foreground->update();
      foreground->render();
   }
}


void Base::managed_on_activate()
{
   if (background) background->activate();
   on_activate();
   if (foreground) foreground->activate();
}


void Base::managed_on_deactivate()
{
   if (background) background->deactivate();
   on_deactivate();
   if (foreground) foreground->deactivate();
}


void Base::on_activate() {}


void Base::on_deactivate() {}
void Base::on_event(ALLEGRO_EVENT *ev) {}
void Base::primary_time_step_func(double time_step_increment, double world_time_after_step) {}
void Base::primary_update_func(double time_now, double delta_time) {}
void Base::primary_render_func() {}
void Base::primary_timer_func() {}
void Base::timer_func() {}
void Base::mouse_axes_func(ALLEGRO_EVENT *ev) {}
void Base::mouse_warp_func(ALLEGRO_EVENT *ev) {}
void Base::display_switch_in_func() {}
void Base::display_switch_out_func() {}
void Base::dialog_system_switch_in_func() {}
void Base::dialog_system_switch_out_func() {}
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


