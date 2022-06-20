

#include <AllegroFlare/ScreenManagers/Dictionary.hpp>

#include <AllegroFlare/Screens/Basic.hpp>

#include <algorithm>
#include <sstream>



namespace AllegroFlare
{
namespace ScreenManagers
{


Dictionary::Dictionary()
   : screens({})
{
}


Dictionary::~Dictionary()
{
}


Screens::Basic *Dictionary::find(std::string identifier)
{
   std::map<std::string, Screens::Basic *>::iterator it = screens.find(identifier);
   if (it == screens.end()) return nullptr;
   return it->second;
}


bool Dictionary::exists(std::string identifier)
{
   std::map<std::string, Screens::Basic *>::iterator it = screens.find(identifier);
   if (it == screens.end()) return false;
   return true;
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

   screens[name] = screen;
   return true;
}


bool Dictionary::remove(Screens::Basic *screen)
{
   //std::map<std::string, Screens::Basic *>::iterator it = screens.begin();

   std::vector<std::string> matching_screen_names;

   for (std::map<std::string, Screens::Basic *>::iterator it=screens.begin(); it!=screens.end(); it++)
   {
      if (it->second == screen) matching_screen_names.push_back(it->first);
   }

   if (matching_screen_names.empty())
   {
      std::stringstream ss;
      ss << "[ScreenManagers::Dictionary::remove(*screen)] warning: No screens found with the pointer value \""
         << screen << "\"." << std::endl;
      return false;
   }
   else
   {
      for (auto &matching_screen_name : matching_screen_names)
      {
         // TODO collect boolean return values, migth be an error
         screens.erase(matching_screen_name);
      }
      return true;
   }

   return true;
}


bool Dictionary::remove(std::string identifier)
{
   std::map<std::string, Screens::Basic *>::iterator it = screens.find(identifier);
   if (it == screens.end())
   {
      std::stringstream ss;
      ss << "[ScreenManagers::Dictionary::remove] warning: A screen listed under the identifier \""
         << identifier << "\" already exists." << std::endl;
      return false;
   }

   screens.erase(it);
   return true;
}


std::map<std::string, Screens::Basic *> Dictionary::get_dictionary_copy()
{
   return screens;
}


void Dictionary::on_events(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      screen.second->on_event(ev);
}


void Dictionary::primary_timer_funcs()
{
   for (auto &screen : screens)
      screen.second->primary_timer_func();
}


void Dictionary::timer_funcs()
{
   for (auto &screen : screens)
      screen.second->timer_func();
}


void Dictionary::display_switch_in_funcs()
{
   for (auto &screen : screens)
      screen.second->display_switch_in_func();
}


void Dictionary::display_switch_out_funcs()
{
   for (auto &screen : screens)
      screen.second->display_switch_out_func();
}


void Dictionary::key_down_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      screen.second->key_down_func(ev);
}


void Dictionary::key_up_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      screen.second->key_up_func(ev);
}


void Dictionary::key_char_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      screen.second->key_char_func(ev);
}


void Dictionary::mouse_axes_funcs()
{
   for (auto &screen : screens)
      screen.second->mouse_axes_func();
}


void Dictionary::mouse_warp_funcs()
{
   for (auto &screen : screens)
      screen.second->mouse_warp_func();
}


void Dictionary::mouse_down_funcs()
{
   for (auto &screen : screens)
      screen.second->mouse_down_func();
}


void Dictionary::mouse_up_funcs()
{
   for (auto &screen : screens)
      screen.second->mouse_up_func();
}


void Dictionary::joy_axis_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      screen.second->joy_axis_func(ev);
}


void Dictionary::joy_button_up_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      screen.second->joy_button_up_func(ev);
}


void Dictionary::joy_button_down_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      screen.second->joy_button_down_func(ev);
}


void Dictionary::joy_config_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      screen.second->joy_config_func(ev);
}


void Dictionary::user_event_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      screen.second->user_event_func(ev);
}


void Dictionary::event_emitter_event_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      screen.second->event_emitter_event_func(ev);
}


void Dictionary::virtual_control_button_up_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      screen.second->virtual_control_button_up_func(ev);
}


void Dictionary::virtual_control_button_down_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      screen.second->virtual_control_button_down_func(ev);
}


void Dictionary::virtual_control_axis_change_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      screen.second->virtual_control_axis_change_func(ev);
}


void Dictionary::native_menu_click_funcs()
{
   for (auto &screen : screens)
      screen.second->native_menu_click_func();
}


} // namespace ScreenManagers
} // namespace AllegroFlare


