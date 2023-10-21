#pragma once


#include <string>
#include <vector>
#include <allegro5/allegro.h>
#include <AllegroFlare/Display.hpp>
#include <AllegroFlare/GameEvent.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>


namespace AllegroFlare
{
   namespace Screens
   {
      class Base
      {
      private:
         std::string type;

      public:
         Base(std::string type="Base");
         virtual ~Base();

         void set_type(std::string type);
         std::string get_type();
         bool is_type(std::string possible_type);

         virtual void managed_primary_timer_func() final; // renders the background and foreground

         virtual void on_activate(); // activated through the manager
         virtual void on_deactivate(); // deactivated thorugh the screen manager
         virtual void on_event(ALLEGRO_EVENT *ev);
         virtual void primary_timer_func();
         virtual void timer_func();
         virtual void display_switch_in_func();
         virtual void display_switch_out_func();
         virtual void mouse_axes_func(ALLEGRO_EVENT *ev);
         virtual void mouse_warp_func(ALLEGRO_EVENT *ev);
         virtual void mouse_down_func(ALLEGRO_EVENT *ev);
         virtual void mouse_up_func(ALLEGRO_EVENT *ev);
         virtual void key_down_func(ALLEGRO_EVENT *ev);
         virtual void key_up_func(ALLEGRO_EVENT *ev);
         virtual void key_char_func(ALLEGRO_EVENT *ev);
         virtual void joy_button_down_func(ALLEGRO_EVENT *ev);
         virtual void joy_button_up_func(ALLEGRO_EVENT *ev);
         virtual void joy_axis_func(ALLEGRO_EVENT *ev);
         virtual void joy_config_func(ALLEGRO_EVENT *ev);
         virtual void user_event_func(ALLEGRO_EVENT *ev);
         virtual void event_emitter_event_func(ALLEGRO_EVENT *ev);
         virtual void game_event_func(AllegroFlare::GameEvent *game_event);
         virtual void virtual_control_button_up_func(
            AllegroFlare::Player* player,
            AllegroFlare::VirtualControllers::Base* virtual_controller,
            int virtual_controller_button_num,
            bool is_repeat=false
         );
         virtual void virtual_control_button_down_func(
            AllegroFlare::Player* player,
            AllegroFlare::VirtualControllers::Base* virtual_controller,
            int virtual_controller_button_num,
            bool is_repeat=false
         );
         //virtual void virtual_control_button_up_func(int player_num, int button_num, bool repeat=false);
         //virtual void virtual_control_button_down_func(int player_num, int button_num, bool repeat=false);
         // TODO: eventually fix the signature on this:
         virtual void virtual_control_axis_change_func(ALLEGRO_EVENT *ev);
         virtual void native_menu_click_func();
      };
   } // namespace Screens
} // namespace AllegroFlare


