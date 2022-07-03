#pragma once


#include <allegro5/allegro.h>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Screens
   {
      class Base;
   };

   namespace ScreenManagers
   {
      class Registry
      {
      private:
         std::vector<Screens::Base *> screens;

      public:
         Registry();
         ~Registry();

         // management
         void add(Screens::Base *screen);
         void remove(Screens::Base *screen);
         void bring_to_front(Screens::Base *s);
         int get_num_screens();

         // for processing
         void on_events(ALLEGRO_EVENT *ev);
         void primary_timer_funcs();
         void timer_funcs();
         void display_switch_in_funcs();
         void display_switch_out_funcs();
         void key_down_funcs(ALLEGRO_EVENT *ev);
         void key_up_funcs(ALLEGRO_EVENT *ev);
         void mouse_axes_funcs();
         void mouse_warp_funcs();
         void mouse_down_funcs();
         void mouse_up_funcs();
         void key_char_funcs(ALLEGRO_EVENT *ev);
         void joy_button_down_funcs(ALLEGRO_EVENT *ev);
         void joy_button_up_funcs(ALLEGRO_EVENT *ev);
         void joy_axis_funcs(ALLEGRO_EVENT *ev);
         void joy_config_funcs(ALLEGRO_EVENT *ev);
         void user_event_funcs(ALLEGRO_EVENT *ev);
         void event_emitter_event_funcs(ALLEGRO_EVENT *ev);
         void virtual_control_button_up_funcs(int player_num, int button_num, bool is_repeat=false);
         void virtual_control_button_down_funcs(int player_num, int button_num, bool is_repeat=false);
         void virtual_control_axis_change_funcs(ALLEGRO_EVENT *ev);
         void native_menu_click_funcs();
      };
   }
}



