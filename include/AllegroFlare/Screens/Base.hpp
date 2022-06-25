#pragma once


#include <string>
#include <vector>
#include <allegro5/allegro.h>
#include <AllegroFlare/Display.hpp>
#include <AllegroFlare/ElementID.hpp>


namespace AllegroFlare
{
   namespace Screens
   {
      class Base : public ElementID
      {
      private:
         std::string type;

      public:
         Base(std::string type="Base");
         virtual ~Base();

         void set_type(std::string type);
         std::string get_type();
         bool is_type(std::string possible_type);

         virtual void on_activate(); // activted through the manager
         virtual void on_deactivate(); // deactivated thorugh the screen manager
         virtual void on_event(ALLEGRO_EVENT *ev);
         virtual void primary_timer_func();
         virtual void timer_func();
         virtual void display_switch_in_func();
         virtual void display_switch_out_func();
         virtual void mouse_axes_func();
         virtual void mouse_warp_func();
         virtual void mouse_down_func();
         virtual void mouse_up_func();
         virtual void key_down_func(ALLEGRO_EVENT *ev);
         virtual void key_up_func(ALLEGRO_EVENT *ev);
         virtual void key_char_func(ALLEGRO_EVENT *ev);
         virtual void joy_button_down_func(ALLEGRO_EVENT *ev);
         virtual void joy_button_up_func(ALLEGRO_EVENT *ev);
         virtual void joy_axis_func(ALLEGRO_EVENT *ev);
         virtual void joy_config_func(ALLEGRO_EVENT *ev);
         virtual void user_event_func(ALLEGRO_EVENT *ev);
         virtual void event_emitter_event_func(ALLEGRO_EVENT *ev);
         virtual void virtual_control_button_up_func(ALLEGRO_EVENT *ev);
         virtual void virtual_control_button_down_func(ALLEGRO_EVENT *ev);
         virtual void virtual_control_axis_change_func(ALLEGRO_EVENT *ev);
         virtual void native_menu_click_func();
      };
   } // namespace Screens
} // namespace AllegroFlare


