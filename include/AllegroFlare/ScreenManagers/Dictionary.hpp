#pragma once


#include <allegro5/allegro.h>
#include <string>
#include <map>
#include <AllegroFlare/GameEvent.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <AllegroFlare/EventEmitter.hpp>


namespace AllegroFlare
{
   namespace Screens
   {
      class Base;
   };

   namespace ScreenManagers
   {
      class Dictionary
      {
      public:
         class Listing
         {
         public:
            Screens::Base* screen;
            bool active;
            bool operator==(const Listing &other) const;
         };

     private:
         std::map<std::string, Listing> screens;
         Listing *find_listing(std::string identifier);
         bool disabled_screens_receive_events;
         AllegroFlare::EventEmitter *event_emitter;
         int deactivate_all_screens_not_of(const std::string& screen_identifier);

      public:
         Dictionary(bool disabled_screens_receive_events=false);
         ~Dictionary();

         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);

         // states
         void allow_disabled_screens_to_receive_events();
         void prevent_disabled_screens_from_receiving_events();

         // management
         // TODO: update to prefer usage of term "identifier" instead of "name"
         Screens::Base *find(std::string identifier);
         std::string find_name(Screens::Base *screen);
         bool exists(Screens::Base *screen);
         bool exists(std::string identifier);

         bool add(std::string name, Screens::Base *screen);
         bool remove(Screens::Base *screen);
         bool remove(std::string identifier);
         //void bring_to_front(Screens::Base *s);
         //void bring_to_front(std::string name);
         bool activate(std::string name);
         std::string get_currently_active_screen_name(); // Deprecated, use get_currently_active_screen_identifier
         std::string get_currently_active_screen_identifier();
         bool is_active(const std::string& identifier);
         //bool deactivate(std::string name); // not to be implemented; screens will be deactivated implicitly
                                              // when a screen is activated through activate();
         //void show(std::string name);
         //void hide(std::string name);
         int get_num_screens();
         bool no_active_screens();
         std::map<std::string, Listing> get_dictionary_copy();

         // for processing
         void on_events(ALLEGRO_EVENT *ev);
         void primary_time_step_funcs(double time_step_increment, double world_time_after_step);
         void primary_update_funcs(double time_now, double delta_time);
         void primary_render_funcs();
         void primary_timer_funcs();
         void timer_funcs();
         void display_switch_in_funcs();
         void display_switch_out_funcs();
         void dialog_system_switch_in_funcs();
         void dialog_system_switch_out_funcs();
         void key_down_funcs(ALLEGRO_EVENT *ev);
         void key_up_funcs(ALLEGRO_EVENT *ev);
         void mouse_axes_funcs(ALLEGRO_EVENT *ev);
         void mouse_warp_funcs(ALLEGRO_EVENT *ev);
         void mouse_down_funcs(ALLEGRO_EVENT *ev);
         void mouse_up_funcs(ALLEGRO_EVENT *ev);
         void key_char_funcs(ALLEGRO_EVENT *ev);
         void joy_button_down_funcs(ALLEGRO_EVENT *ev);
         void joy_button_up_funcs(ALLEGRO_EVENT *ev);
         void joy_axis_funcs(ALLEGRO_EVENT *ev);
         void joy_config_funcs(ALLEGRO_EVENT *ev);
         void user_event_funcs(ALLEGRO_EVENT *ev);
         void event_emitter_event_funcs(ALLEGRO_EVENT *ev);
         void game_event_funcs(AllegroFlare::GameEvent *game_event);
         void virtual_control_button_up_funcs(
            AllegroFlare::Player* player,
            AllegroFlare::VirtualControllers::Base* virtual_controller,
            int virtual_controller_button_num,
            bool is_repeat=false
         );
         void virtual_control_button_down_funcs(
            AllegroFlare::Player* player,
            AllegroFlare::VirtualControllers::Base* virtual_controller,
            int virtual_controller_button_num,
            bool is_repeat=false
         );
         void virtual_control_axis_change_funcs(ALLEGRO_EVENT *ev);
         void native_menu_click_funcs();
      };
   }
}



