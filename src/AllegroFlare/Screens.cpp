

#include <AllegroFlare/Screens.hpp>

#include <AllegroFlare/Screen.hpp>

#include <algorithm>


namespace AllegroFlare
{
   Screens::Screens()
      : screens({})
   {
   }


   Screens::~Screens()
   {
   }


   void Screens::add(Screen *screen)
   {
      screens.push_back(screen);
   }


   void Screens::remove(Screen *screen) // should probably test this
   {
      std::vector<Screen *>::iterator it = std::find(screens.begin(), screens.end(), screen);
      screens.erase(it);
   }


   void Screens::on_events(ALLEGRO_EVENT *ev)
   {
      for (unsigned i=0; i<screens.size(); i++)
         screens[i]->on_event(ev);
   }


   void Screens::primary_timer_funcs()
   {
      // do screens with NULL displays first
      for (unsigned i=0; i<screens.size(); i++)
      {
         if (screens[i]->display == NULL) screens[i]->primary_timer_func();
      }

      // then do screens in order sorted by displays.
      for (unsigned d=0; d<Display::displays.size(); d++)
      {
         Display::displays[d]->set_as_target_bitmap();
         for (unsigned i=0; i<screens.size(); i++)
         {
            if (screens[i]->display == Display::displays[d])
            {
               screens[i]->prepare_drawing_state();
               screens[i]->primary_timer_func();
            }
         }
         Display::displays[d]->flip();
      }
   }


   void Screens::timer_funcs()
   {
      for (unsigned i=0; i<screens.size(); i++)
         screens[i]->timer_func();
   }


   void Screens::display_switch_in_funcs()
   {
      for (unsigned d=0; d<Display::displays.size(); d++)
      {
         for (unsigned i=0; i<screens.size(); i++)
         {
            if (screens[i]->display == NULL || screens[i]->display == Display::displays[d])
               screens[i]->display_switch_in_func();
         }
      }
   }


   void Screens::display_switch_out_funcs()
   {
      for (unsigned d=0; d<Display::displays.size(); d++)
      {
         for (unsigned i=0; i<screens.size(); i++)
         {
            if (screens[i]->display == NULL || screens[i]->display == Display::displays[d])
               screens[i]->display_switch_out_func();
         }
      }
   }


   void Screens::key_down_funcs(ALLEGRO_EVENT *ev)
   {
      for (unsigned i=0; i<screens.size(); i++)
         screens[i]->key_down_func(ev);
   }


   void Screens::key_up_funcs()
   {
      for (unsigned i=0; i<screens.size(); i++)
         screens[i]->key_up_func();
   }


   void Screens::key_char_funcs(ALLEGRO_EVENT *ev)
   {
      for (unsigned i=0; i<screens.size(); i++)
         screens[i]->key_char_func(ev);
   }


   void Screens::mouse_axes_funcs()
   {
      for (unsigned i=0; i<screens.size(); i++)
         screens[i]->mouse_axes_func();
   }


   void Screens::mouse_warp_funcs()
   {
      for (unsigned i=0; i<screens.size(); i++)
         screens[i]->mouse_warp_func();
   }


   void Screens::mouse_down_funcs()
   {
      for (unsigned i=0; i<screens.size(); i++)
         screens[i]->mouse_down_func();
   }


   void Screens::mouse_up_funcs()
   {
      for (unsigned i=0; i<screens.size(); i++)
         screens[i]->mouse_up_func();
   }


   void Screens::joy_axis_funcs()
   {
      for (unsigned i=0; i<screens.size(); i++)
         screens[i]->joy_axis_func();
   }


   void Screens::joy_button_up_funcs()
   {
      for (unsigned i=0; i<screens.size(); i++)
         screens[i]->joy_button_up_func();
   }


   void Screens::joy_button_down_funcs()
   {
      for (unsigned i=0; i<screens.size(); i++)
         screens[i]->joy_button_down_func();
   }


   void Screens::joy_config_funcs()
   {
      for (unsigned i=0; i<screens.size(); i++)
         screens[i]->joy_config_func();
   }


   void Screens::user_event_funcs()
   {
      for (unsigned i=0; i<screens.size(); i++)
         screens[i]->user_event_func();
   }


   void Screens::native_menu_click_funcs()
   {
      for (unsigned i=0; i<screens.size(); i++)
         screens[i]->native_menu_click_func();
   }


   void Screens::send_signal(int signal, void *data)
   {
      for (unsigned i=0; i<screens.size(); i++)
         screens[i]->receive_signal(signal, data);
   }


   void Screens::send_signal(std::string const signal, void *data)
   {
      for (unsigned i=0; i<screens.size(); i++)
         screens[i]->receive_signal(signal, data);
   }


   bool Screens::signal_has_header(std::string header, std::string signal)
   {
      return (signal.substr(0, header.length()) == header);
   }


   std::string Screens::strip_signal_header(std::string header, std::string signal)
   {
      return signal.substr(header.length(), signal.length()-header.length());
      return "";
   }


   void Screens::bring_to_front(Screen *s)
   {
      if (!s) return;

      for (unsigned i=0; i<screens.size(); i++)
      {
         if (screens[i] == s)
         {
            screens.erase(screens.begin()+i);
            break;
         }
      }
      screens.push_back(s);
   }


   int Screens::get_num_screens()
   {
      return screens.size();
   }
}


