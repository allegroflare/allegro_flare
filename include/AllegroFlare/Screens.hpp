#pragma once


#include <allegro5/allegro.h>
#include <string>
#include <vector>


namespace AllegroFlare
{
   class Screen;


   class Screens
   {
   private:
      std::vector<Screen *> screens;

   public:
      Screens();
      ~Screens();

      void add(Screen *screen);
      void remove(Screen *screen);

      void on_events(ALLEGRO_EVENT *ev);
      void primary_timer_funcs();
      void timer_funcs();
      void display_switch_in_funcs();
      void display_switch_out_funcs();
      void key_down_funcs(ALLEGRO_EVENT *ev);
      void key_up_funcs();
      void mouse_axes_funcs();
      void mouse_warp_funcs();
      void mouse_down_funcs();
      void mouse_up_funcs();
      void key_char_funcs(ALLEGRO_EVENT *ev);
      void joy_button_down_funcs();
      void joy_button_up_funcs();
      void joy_axis_funcs();
      void joy_config_funcs();
      void user_event_funcs();
      void native_menu_click_funcs();

      void send_signal(int signal, void *data);
      void send_signal(std::string const signal, void *data);
      bool signal_has_header(std::string header, std::string signal);
      std::string strip_signal_header(std::string header, std::string signal);
      void bring_to_front(Screen *s);
      int get_num_screens();
   };
}


