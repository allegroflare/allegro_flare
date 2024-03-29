

#include <AllegroFlare/ScreenManagers/Registry.hpp>

#include <AllegroFlare/Screens/Base.hpp>

#include <algorithm>



namespace AllegroFlare
{
namespace ScreenManagers
{


Registry::Registry()
   : screens({})
{
}


Registry::~Registry()
{
}


void Registry::add(Screens::Base *screen)
{
   screens.push_back(screen);
}


void Registry::remove(Screens::Base *screen) // should probably test this
{
   std::vector<Screens::Base *>::iterator it = std::find(screens.begin(), screens.end(), screen);
   screens.erase(it);
}


void Registry::on_events(ALLEGRO_EVENT *ev)
{
   for (unsigned i=0; i<screens.size(); i++)
      screens[i]->on_event(ev);
}


void Registry::primary_timer_funcs()
{
   for (unsigned i=0; i<screens.size(); i++)
      screens[i]->primary_timer_func();
}


void Registry::timer_funcs()
{
   for (unsigned i=0; i<screens.size(); i++)
      screens[i]->timer_func();
}


void Registry::display_switch_in_funcs()
{
   for (unsigned i=0; i<screens.size(); i++)
      screens[i]->display_switch_in_func();
}


void Registry::display_switch_out_funcs()
{
   for (unsigned i=0; i<screens.size(); i++)
      screens[i]->display_switch_out_func();
}


void Registry::key_down_funcs(ALLEGRO_EVENT *ev)
{
   for (unsigned i=0; i<screens.size(); i++)
      screens[i]->key_down_func(ev);
}


void Registry::key_up_funcs(ALLEGRO_EVENT *ev)
{
   for (unsigned i=0; i<screens.size(); i++)
      screens[i]->key_up_func(ev);
}


void Registry::key_char_funcs(ALLEGRO_EVENT *ev)
{
   for (unsigned i=0; i<screens.size(); i++)
      screens[i]->key_char_func(ev);
}


void Registry::mouse_axes_funcs(ALLEGRO_EVENT *ev)
{
   for (unsigned i=0; i<screens.size(); i++)
      screens[i]->mouse_axes_func(ev);
}


void Registry::mouse_warp_funcs(ALLEGRO_EVENT *ev)
{
   for (unsigned i=0; i<screens.size(); i++)
      screens[i]->mouse_warp_func(ev);
}


void Registry::mouse_down_funcs(ALLEGRO_EVENT *ev)
{
   for (unsigned i=0; i<screens.size(); i++)
      screens[i]->mouse_down_func(ev);
}


void Registry::mouse_up_funcs(ALLEGRO_EVENT *ev)
{
   for (unsigned i=0; i<screens.size(); i++)
      screens[i]->mouse_up_func(ev);
}


void Registry::joy_axis_funcs(ALLEGRO_EVENT *ev)
{
   for (unsigned i=0; i<screens.size(); i++)
      screens[i]->joy_axis_func(ev);
}


void Registry::joy_button_up_funcs(ALLEGRO_EVENT *ev)
{
   for (unsigned i=0; i<screens.size(); i++)
      screens[i]->joy_button_up_func(ev);
}


void Registry::joy_button_down_funcs(ALLEGRO_EVENT *ev)
{
   for (unsigned i=0; i<screens.size(); i++)
      screens[i]->joy_button_down_func(ev);
}


void Registry::joy_config_funcs(ALLEGRO_EVENT *ev)
{
   for (unsigned i=0; i<screens.size(); i++)
      screens[i]->joy_config_func(ev);
}


void Registry::user_event_funcs(ALLEGRO_EVENT *ev)
{
   for (unsigned i=0; i<screens.size(); i++)
      screens[i]->user_event_func(ev);
}


void Registry::event_emitter_event_funcs(ALLEGRO_EVENT *ev)
{
   for (unsigned i=0; i<screens.size(); i++)
      screens[i]->event_emitter_event_func(ev);
}


void Registry::virtual_control_button_up_funcs(
   AllegroFlare::Player* player,
   AllegroFlare::VirtualControllers::Base* virtual_controller,
   int virtual_controller_button_num,
   bool is_repeat
)
{
   for (auto &screen : screens)
      screen->virtual_control_button_up_func(
            player,
            virtual_controller,
            virtual_controller_button_num,
            is_repeat
      );
}


void Registry::virtual_control_button_down_funcs(
   AllegroFlare::Player* player,
   AllegroFlare::VirtualControllers::Base* virtual_controller,
   int virtual_controller_button_num,
   bool is_repeat
)
{
   for (auto &screen : screens)
      screen->virtual_control_button_down_func(
            player,
            virtual_controller,
            virtual_controller_button_num,
            is_repeat
      );
}


//void Registry::virtual_control_button_up_funcs(int player_num, int button_num, bool is_repeat)
//{
   //for (unsigned i=0; i<screens.size(); i++)
      //screens[i]->virtual_control_button_up_func(player_num, button_num, is_repeat);
//}


//void Registry::virtual_control_button_down_funcs(int player_num, int button_num, bool is_repeat)
//{
   //for (unsigned i=0; i<screens.size(); i++)
      //screens[i]->virtual_control_button_down_func(player_num, button_num, is_repeat);
//}


void Registry::virtual_control_axis_change_funcs(ALLEGRO_EVENT *ev)
{
   for (unsigned i=0; i<screens.size(); i++)
      screens[i]->virtual_control_axis_change_func(ev);
}


void Registry::native_menu_click_funcs()
{
   for (unsigned i=0; i<screens.size(); i++)
      screens[i]->native_menu_click_func();
}


void Registry::bring_to_front(Screens::Base *s)
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


} // namespace ScreenManagers
} // namespace AllegroFlare


