

#include <AllegroFlare/ScreenManagers/Dictionary.hpp>

#include <AllegroFlare/Screens/Base.hpp>

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


Dictionary::Dictionary(bool disabled_screens_receive_events)
   : screens({})
   , disabled_screens_receive_events(disabled_screens_receive_events)
{
}


Dictionary::~Dictionary()
{
}


void Dictionary::allow_disabled_screens_to_receive_events()
{
   disabled_screens_receive_events = true;
}


void Dictionary::prevent_disabled_screens_from_receiving_events()
{
   disabled_screens_receive_events = false;
}


Dictionary::Listing *Dictionary::find_listing(std::string identifier)
{
   std::map<std::string, Listing>::iterator it = screens.find(identifier);
   if (it == screens.end()) return nullptr;
   return (&it->second);
}


Screens::Base *Dictionary::find(std::string identifier)
{
   std::map<std::string, Listing>::iterator it = screens.find(identifier);
   if (it == screens.end()) return nullptr;
   return it->second.screen;
}


std::string Dictionary::find_name(Screens::Base *screen)
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


bool Dictionary::exists(Screens::Base *screen)
{
   for (std::map<std::string, Listing>::iterator it=screens.begin(); it!=screens.end(); it++)
   {
      if (it->second.screen == screen) return true;
   }
   return false;
}


bool Dictionary::add(std::string name, Screens::Base *screen)
{
   // TODO: prevent an empty string from being a valid name
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


bool Dictionary::remove(Screens::Base *screen)
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
   // obtain record
   Listing *listing = Dictionary::find_listing(identifier);

   // validate exists
   if (listing == nullptr)
   {
      return false; // TODO add warning message
   }

   // validate is not already active
   if (listing->active)
   {
      return false; // TODO add warning message
   }

   // activate screen and deactivate all other screens that are active
   bool activated = false;
   for (auto &screen : screens)
   {
      if (&screen.second == listing)
      {
         screen.second.active = true;
         if (screen.second.screen) screen.second.screen->on_activate();
         else
         {
            // TODO: show warning, could not activate, no screen
         }
         activated = true;
      }
      else if (screen.second.active)
      {
         screen.second.active = false;
         if (screen.second.screen) screen.second.screen->on_deactivate();
      }
   }
   return activated;
}



std::string Dictionary::get_currently_active_screen_name()
{
   for (auto &screen : screens) if (screen.second.active) return screen.first;
   return "";
}



std::map<std::string, Dictionary::Listing> Dictionary::get_dictionary_copy()
{
   return screens;
}


void Dictionary::on_events(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
         screen.second.screen->on_event(ev);
}


void Dictionary::primary_timer_funcs()
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
         screen.second.screen->primary_timer_func();
}


void Dictionary::timer_funcs()
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
         screen.second.screen->timer_func();
}


void Dictionary::display_switch_in_funcs()
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
         screen.second.screen->display_switch_in_func();
}


void Dictionary::display_switch_out_funcs()
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
         screen.second.screen->display_switch_out_func();
}


void Dictionary::key_down_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
         screen.second.screen->key_down_func(ev);
}


void Dictionary::key_up_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
         screen.second.screen->key_up_func(ev);
}


void Dictionary::key_char_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
         screen.second.screen->key_char_func(ev);
}


void Dictionary::mouse_axes_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
         screen.second.screen->mouse_axes_func(ev);
}


void Dictionary::mouse_warp_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
         screen.second.screen->mouse_warp_func(ev);
}


void Dictionary::mouse_down_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
         screen.second.screen->mouse_down_func(ev);
}


void Dictionary::mouse_up_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
         screen.second.screen->mouse_up_func(ev);
}


void Dictionary::joy_axis_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
         screen.second.screen->joy_axis_func(ev);
}


void Dictionary::joy_button_up_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
         screen.second.screen->joy_button_up_func(ev);
}


void Dictionary::joy_button_down_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
         screen.second.screen->joy_button_down_func(ev);
}


void Dictionary::joy_config_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
         screen.second.screen->joy_config_func(ev);
}


void Dictionary::user_event_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
         screen.second.screen->user_event_func(ev);
}


void Dictionary::event_emitter_event_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
         screen.second.screen->event_emitter_event_func(ev);
}


void Dictionary::game_event_funcs(AllegroFlare::GameEvent *game_event)
   // "game events" will be sent to all screens even if they have been deactivated.
   // "game events" needs to be renamed to something else like "system events", "global events",
   // or something similar. They are meant to be events that the game designer themselves would use
   // to manage the top-level global view of their game, so that other events within the AllegroFlare system
   // should be out of view
{
   for (auto &screen : screens) //
      //if (screen.second.active)
      {
         screen.second.screen->game_event_func(game_event);
      }
}


void Dictionary::virtual_control_button_up_funcs(int player_num, int button_num, bool is_repeat)
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
         screen.second.screen->virtual_control_button_up_func(player_num, button_num, is_repeat);
}


void Dictionary::virtual_control_button_down_funcs(int player_num, int button_num, bool is_repeat)
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
         screen.second.screen->virtual_control_button_down_func(player_num, button_num, is_repeat);
}


void Dictionary::virtual_control_axis_change_funcs(ALLEGRO_EVENT *ev)
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
         screen.second.screen->virtual_control_axis_change_func(ev);
}


void Dictionary::native_menu_click_funcs()
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
         screen.second.screen->native_menu_click_func();
}


} // namespace ScreenManagers
} // namespace AllegroFlare


