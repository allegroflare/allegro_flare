#pragma once


#include <allegro5/allegro.h>
#include <string>
#include <map>


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

      public:
         Dictionary();
         ~Dictionary();

         // management
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
         //bool deactivate(std::string name); // not to be implemented; screens will be deactivated implicitly
                                              // when a screen is activated through activate();
         //void show(std::string name);
         //void hide(std::string name);
         int get_num_screens();
         std::map<std::string, Listing> get_dictionary_copy();

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
         void virtual_control_button_up_funcs(ALLEGRO_EVENT *ev);
         void virtual_control_button_down_funcs(ALLEGRO_EVENT *ev);
         void virtual_control_axis_change_funcs(ALLEGRO_EVENT *ev);
         void native_menu_click_funcs();
      };
   }
}



