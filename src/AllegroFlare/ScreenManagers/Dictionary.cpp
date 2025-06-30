

#include <AllegroFlare/ScreenManagers/Dictionary.hpp>

#include <AllegroFlare/Screens/Base.hpp>

#include <AllegroFlare/Logger.hpp>
//#include <AllegroFlare/EventNames.hpp>
#include <algorithm>
#include <sstream>


#include <iostream>



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
   , event_emitter(nullptr)
{
}


Dictionary::~Dictionary()
{
}


void Dictionary::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


int Dictionary::deactivate_all_screens_not_of(const std::string& screen_identifier)
{
   // TODO: Include emitting events
   int num_screens_deactivated = 0;

   if (!event_emitter)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::ScreenManagers::Dictionary::deactivate_all_screens_not_of",
         "guard: (event_emitter != nullptr) not met."
      );
   }

   // obtain record
   Listing *listing = Dictionary::find_listing(screen_identifier);

   // validate exists
   //if (listing == nullptr)
   //{
      //std::stringstream error_message;
      //error_message << "Cannot activate screen \"" << screen_identifier << "\". No such screen exists.";
      //AllegroFlare::Logger::throw_error("AllegroFlare::ScreenManagers::Dictionary::activate", error_message.str());
   //}

   // validate is not already active
   //if (listing->active)
   //{
      //return 0; // TODO add warning message
   //}

   // activate screen and deactivate all other screens that are active
   for (auto &screen : screens)
   {
      if (listing != nullptr && &screen.second == listing)
      {
         // This is the screen to NOT deactivate, so do nothing

         //screen.second.active = true;
         //if (screen.second.screen)
         //{
            //screen.second.screen->on_activate();
            //// TODO: emit ALLEGRO_FLARE_EVENT_SCREEN_ACTIVATED
            //// TODO: emit ALLEGRO_FLARE_EVENT_SCREEN_DEACTIVATED
         //}
         //else
         //{
            //// TODO: show warning, could not activate, no screen
         //}
         //event_emitter->emit_screen_activated_event(screen_identifier);
      }
      else if (screen.second.active)
      {
         screen.second.active = false;
         num_screens_deactivated++;
         if (screen.second.screen)
         {
            screen.second.screen->managed_on_deactivate();
            // TODO: emit ALLEGRO_FLARE_EVENT_SCREEN_DEACTIVATED
         }
         else
         {
            // TODO: show warning, could not activate, no screen
         }
         //event_emitter->emit_screen_deactivated_event(screen_identifier); // NOTE: This feature could added if needed
      }
   }
   return num_screens_deactivated;
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
   if (name.empty())
   {
      std::stringstream error_message;
      error_message << "A screen name cannot be blank.";
      AllegroFlare::Logger::throw_error("AllegroFlare::ScreenManagers::Dictionary::add", error_message.str());
      return false;
   }

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
      throw std::runtime_error("[Dictionary::remove]: critical error: This feature is currently not implemented. "
                               "If you need it, it wouldn't be hard to implement. There's already code that does "
                               "all the work it just needs to be assembled. Note that removing the object does not "
                               "destroy it."
                               );
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
   if (!event_emitter)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::ScreenManagers::Dictionary::activate",
         "guard: (event_emitter != nullptr) not met."
      );
   }

   // obtain record
   Listing *listing = Dictionary::find_listing(identifier);

   // validate exists
   if (listing == nullptr)
   {
      std::stringstream error_message;
      error_message << "Cannot activate screen \"" << identifier << "\". No such screen exists.";
      AllegroFlare::Logger::throw_error("AllegroFlare::ScreenManagers::Dictionary::activate", error_message.str());
   }

   // validate is not already active
   if (listing->active)
   {
      return false; // TODO add warning message
   }

   // Deactivate all screens not of the screen to activate
   deactivate_all_screens_not_of(identifier);

   // activate screen and deactivate all other screens that are active
   bool activated = false;
   for (auto &screen : screens)
   {
      if (&screen.second == listing)
      {
         screen.second.active = true;
         if (screen.second.screen)
         {
            screen.second.screen->managed_on_activate();
            // TODO: emit ALLEGRO_FLARE_EVENT_SCREEN_ACTIVATED
            // TODO: emit ALLEGRO_FLARE_EVENT_SCREEN_DEACTIVATED
         }
         else
         {
            // TODO: show warning, could not activate, no screen
         }
         event_emitter->emit_screen_activated_event(identifier);
         activated = true;
      }
      //else if (screen.second.active)
      //{
         //screen.second.active = false;
         //if (screen.second.screen)
         //{
            ////screen.second.screen->on_deactivate();
            // TODO: emit ALLEGRO_FLARE_EVENT_SCREEN_DEACTIVATED
         //}
         //else
         //{
            //// TODO: show warning, could not activate, no screen
         //}
         ////event_emitter->emit_screen_deactivated_event(identifier); // Not supported
      //}
   }
   return activated;
}


std::string Dictionary::get_currently_active_screen_name()
{
   AllegroFlare::Logger::warn_from_once(
         "AllegroFlare::ScreenManagers::Dictionary::get_currently_active_screen_name",
         "This method is deprecated. Use \"get_currently_active_screen_identifier\" instead, which is identical in use."
      );
   return get_currently_active_screen_identifier();
}


std::string Dictionary::get_currently_active_screen_identifier()
{
   for (auto &screen : screens) if (screen.second.active) return screen.first;
   return "";
}


bool Dictionary::is_active(const std::string& identifier)
{
   if (screens.count(identifier) == 0)
   {
      AllegroFlare::Logger::throw_error(
            "AllegroFlare::ScreenManagers::Dictionary::is_active",
            "Screen named \"" + identifier + "\" does not exist."
         );
   }
   return screens[identifier].active;
}


bool Dictionary::no_active_screens()
{
   for (auto &screen : screens) if (screen.second.active) return false;
   return true;
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


void Dictionary::primary_time_step_funcs(double time_step_increment, double world_time_after_step)
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
      {
         if (!screen.second.screen->is_using_update_strategy(
            AllegroFlare::Screens::Base::UpdateStrategy::SEPARATE_UPDATE_AND_RENDER_FUNCS)
         ) continue;

         screen.second.screen->managed_primary_time_step_func(time_step_increment, world_time_after_step);
      }
}


void Dictionary::primary_update_funcs(double time_now, double delta_time)
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
      {
         if (!screen.second.screen->is_using_update_strategy(
            AllegroFlare::Screens::Base::UpdateStrategy::SEPARATE_UPDATE_AND_RENDER_FUNCS)
         ) continue;

         screen.second.screen->managed_primary_update_func(time_now, delta_time);
      }
}


void Dictionary::primary_render_funcs()
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
      {
         if (!screen.second.screen->is_using_update_strategy(
            AllegroFlare::Screens::Base::UpdateStrategy::SEPARATE_UPDATE_AND_RENDER_FUNCS)
         ) continue;

         screen.second.screen->managed_primary_render_func();
      }
}


void Dictionary::primary_timer_funcs()
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
      {
         if (!screen.second.screen->is_using_update_strategy(
            AllegroFlare::Screens::Base::UpdateStrategy::LEGACY_SINGLE_PRIMARY_TIMER_FUNC)
         ) continue;

         screen.second.screen->managed_primary_timer_func();
      }
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


void Dictionary::dialog_system_switch_in_funcs()
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
         screen.second.screen->dialog_system_switch_in_func();
}


void Dictionary::dialog_system_switch_out_funcs()
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
         screen.second.screen->dialog_system_switch_out_func();
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


void Dictionary::virtual_control_button_up_funcs(
   AllegroFlare::Player* player,
   AllegroFlare::VirtualControllers::Base* virtual_controller,
   int virtual_controller_button_num,
   bool is_repeat
)
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
         screen.second.screen->virtual_control_button_up_func(
               player,
               virtual_controller,
               virtual_controller_button_num,
               is_repeat
         );
}


void Dictionary::virtual_control_button_down_funcs(
   AllegroFlare::Player* player,
   AllegroFlare::VirtualControllers::Base* virtual_controller,
   int virtual_controller_button_num,
   bool is_repeat
)
{
   for (auto &screen : screens)
      if (disabled_screens_receive_events || screen.second.active)
         screen.second.screen->virtual_control_button_down_func(
               player,
               virtual_controller,
               virtual_controller_button_num,
               is_repeat
         );
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


