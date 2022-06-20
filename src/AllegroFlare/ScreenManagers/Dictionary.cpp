

#include <AllegroFlare/ScreenManagers/Dictionary.hpp>

#include <AllegroFlare/Screens/Basic.hpp>

#include <algorithm>
#include <sstream>



namespace AllegroFlare
{
namespace ScreenManagers
{


bool Dictionary::Listing::operator==(const Listing &other) const
{
   if (
         (other.active != active)
      || (other.screen != screen)
      )
   {
      return false;
   }
   return true;
}


Dictionary::Dictionary()
   : screens({})
{
}


Dictionary::~Dictionary()
{
}


Screens::Basic *Dictionary::find(std::string identifier)
{
   std::map<std::string, Listing>::iterator it = screens.find(identifier);
   if (it == screens.end()) return nullptr;
   return it->second.screen;
}


std::string Dictionary::find_name(Screens::Basic *screen)
{
   for (std::map<std::string, Listing>::iterator it=screens.begin(); it!=screens.end(); it++)
   {
      if (it->second.screen == screen) return it->first;
   }
   return "";
}


bool Dictionary::exists(std::string identifier)
{
   std::map<std::string, Listing>::iterator it = screens.find(identifier);
   if (it == screens.end()) return false;
   return true;
}


bool Dictionary::exists(Screens::Basic *screen)
{
   for (std::map<std::string, Listing>::iterator it=screens.begin(); it!=screens.end(); it++)
   {
      if (it->second.screen == screen) return true;
   }
   return false;
}


bool Dictionary::add(std::string name, Screens::Basic *screen)
{
   if (exists(name))
   {
      std::stringstream error_message;
      error_message << "[ScreenManagers::Dictionary::add] warning: A screen listed under the identifier \""
         << name << "\" already exists.";
      std::cout << error_message.str() << std::endl;
      return false;
   }

   screens[name] = Listing{screen, false};
   return true;
}


bool Dictionary::remove(Screens::Basic *screen)
{
   if (!exists(screen))
   {
      std::stringstream ss;
      ss << "[ScreenManagers::Dictionary::remove(*screen)] warning: No screens found with the pointer value \""
         << screen << "\"." << std::endl;
      return false;
   }
   else
   {
      
      return true;
   }

   return true;
}


bool Dictionary::remove(std::string identifier)
{
   std::map<std::string, Listing>::iterator it = screens.find(identifier);
   if (it == screens.end())
   {
      std::stringstream ss;
      ss << "[ScreenManagers::Dictionary::remove] warning: A screen listed under the identifier \""
         << identifier << "\" does not exist." << std::endl;
      return false;
   }

   screens.erase(it);
   return true;
}


bool Dictionary::activate(std::string identifier)
{
   // deactivate all screens except current screen
   return false;
}


bool Dictionary::deactivate(std::string identifier)
{
   // activate all screens
   return false;
}


std::map<std::string, Dictionary::Listing> Dictionary::get_dictionary_copy()
{
   return screens;
}


void Dictionary::on_events(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      screen.second.screen->on_event(ev);
}


void Dictionary::primary_timer_funcs()
{
   for (auto &screen : screens)
      screen.second.screen->primary_timer_func();
}


void Dictionary::timer_funcs()
{
   for (auto &screen : screens)
      screen.second.screen->timer_func();
}


void Dictionary::display_switch_in_funcs()
{
   for (auto &screen : screens)
      screen.second.screen->display_switch_in_func();
}


void Dictionary::display_switch_out_funcs()
{
   for (auto &screen : screens)
      screen.second.screen->display_switch_out_func();
}


void Dictionary::key_down_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      screen.second.screen->key_down_func(ev);
}


void Dictionary::key_up_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      screen.second.screen->key_up_func(ev);
}


void Dictionary::key_char_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      screen.second.screen->key_char_func(ev);
}


void Dictionary::mouse_axes_funcs()
{
   for (auto &screen : screens)
      screen.second.screen->mouse_axes_func();
}


void Dictionary::mouse_warp_funcs()
{
   for (auto &screen : screens)
      screen.second.screen->mouse_warp_func();
}


void Dictionary::mouse_down_funcs()
{
   for (auto &screen : screens)
      screen.second.screen->mouse_down_func();
}


void Dictionary::mouse_up_funcs()
{
   for (auto &screen : screens)
      screen.second.screen->mouse_up_func();
}


void Dictionary::joy_axis_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      screen.second.screen->joy_axis_func(ev);
}


void Dictionary::joy_button_up_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      screen.second.screen->joy_button_up_func(ev);
}


void Dictionary::joy_button_down_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      screen.second.screen->joy_button_down_func(ev);
}


void Dictionary::joy_config_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      screen.second.screen->joy_config_func(ev);
}


void Dictionary::user_event_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      screen.second.screen->user_event_func(ev);
}


void Dictionary::event_emitter_event_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      screen.second.screen->event_emitter_event_func(ev);
}


void Dictionary::virtual_control_button_up_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      screen.second.screen->virtual_control_button_up_func(ev);
}


void Dictionary::virtual_control_button_down_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      screen.second.screen->virtual_control_button_down_func(ev);
}


void Dictionary::virtual_control_axis_change_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      screen.second.screen->virtual_control_axis_change_func(ev);
}


void Dictionary::native_menu_click_funcs()
{
   for (auto &screen : screens)
      screen.second.screen->native_menu_click_func();
}


} // namespace ScreenManagers
} // namespace AllegroFlare


