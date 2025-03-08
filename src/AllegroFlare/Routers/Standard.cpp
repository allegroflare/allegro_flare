

#include <AllegroFlare/Routers/Standard.hpp>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/RouteEventDatas/ActivateScreenByIdentifier.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>


namespace AllegroFlare
{
namespace Routers
{


Standard::Standard(AllegroFlare::EventEmitter* event_emitter, std::function<bool(AllegroFlare::RouteEventDatas::Base*)> load_level_handler)
   : AllegroFlare::Routers::Base(AllegroFlare::Routers::Standard::TYPE)
   , event_emitter(event_emitter)
   , load_level_handler(load_level_handler)
   , game_session()
   , on_route_event_unhandled_func({})
   , on_route_event_unhandled_func_user_data(nullptr)
   , on_load_last_played_session_or_start_new_func({})
   , on_load_last_played_session_or_start_new_func_user_data(nullptr)
   , on_create_new_session_func({})
   , on_create_new_session_func_user_data(nullptr)
   , on_continue_from_last_save_func({})
   , on_continue_from_last_save_func_user_data(nullptr)
   , on_load_save_file_content_into_gameplay_func({})
   , on_load_save_file_content_into_gameplay_func_user_data(nullptr)
   , on_gameplay_paused_func({})
   , on_gameplay_paused_func_user_data(nullptr)
   , on_gameplay_unpaused_func({})
   , on_gameplay_unpaused_func_user_data(nullptr)
   , on_primary_gameplay_screen_finished_func({})
   , on_primary_gameplay_screen_finished_func_user_data(nullptr)
   , on_arbitrary_storyboard_screen_finished_func({})
   , on_arbitrary_storyboard_screen_finished_func_user_data(nullptr)
   , on_arbitrary_storyboard_screen_activated_func({})
   , on_arbitrary_storyboard_screen_activated_func_user_data(nullptr)
{
}


Standard::~Standard()
{
}


void Standard::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void Standard::set_load_level_handler(std::function<bool(AllegroFlare::RouteEventDatas::Base*)> load_level_handler)
{
   this->load_level_handler = load_level_handler;
}


void Standard::set_on_route_event_unhandled_func(std::function<bool(uint32_t, AllegroFlare::Routers::Standard*, void*)> on_route_event_unhandled_func)
{
   this->on_route_event_unhandled_func = on_route_event_unhandled_func;
}


void Standard::set_on_route_event_unhandled_func_user_data(void* on_route_event_unhandled_func_user_data)
{
   this->on_route_event_unhandled_func_user_data = on_route_event_unhandled_func_user_data;
}


void Standard::set_on_load_last_played_session_or_start_new_func(std::function<void(AllegroFlare::Routers::Standard*, void*)> on_load_last_played_session_or_start_new_func)
{
   this->on_load_last_played_session_or_start_new_func = on_load_last_played_session_or_start_new_func;
}


void Standard::set_on_load_last_played_session_or_start_new_func_user_data(void* on_load_last_played_session_or_start_new_func_user_data)
{
   this->on_load_last_played_session_or_start_new_func_user_data = on_load_last_played_session_or_start_new_func_user_data;
}


void Standard::set_on_create_new_session_func(std::function<void(AllegroFlare::Routers::Standard*, void*)> on_create_new_session_func)
{
   this->on_create_new_session_func = on_create_new_session_func;
}


void Standard::set_on_create_new_session_func_user_data(void* on_create_new_session_func_user_data)
{
   this->on_create_new_session_func_user_data = on_create_new_session_func_user_data;
}


void Standard::set_on_continue_from_last_save_func(std::function<void(AllegroFlare::Routers::Standard*, void*)> on_continue_from_last_save_func)
{
   this->on_continue_from_last_save_func = on_continue_from_last_save_func;
}


void Standard::set_on_continue_from_last_save_func_user_data(void* on_continue_from_last_save_func_user_data)
{
   this->on_continue_from_last_save_func_user_data = on_continue_from_last_save_func_user_data;
}


void Standard::set_on_load_save_file_content_into_gameplay_func(std::function<void(AllegroFlare::Routers::Standard*, void*)> on_load_save_file_content_into_gameplay_func)
{
   this->on_load_save_file_content_into_gameplay_func = on_load_save_file_content_into_gameplay_func;
}


void Standard::set_on_load_save_file_content_into_gameplay_func_user_data(void* on_load_save_file_content_into_gameplay_func_user_data)
{
   this->on_load_save_file_content_into_gameplay_func_user_data = on_load_save_file_content_into_gameplay_func_user_data;
}


void Standard::set_on_gameplay_paused_func(std::function<void(AllegroFlare::Routers::Standard*, void*)> on_gameplay_paused_func)
{
   this->on_gameplay_paused_func = on_gameplay_paused_func;
}


void Standard::set_on_gameplay_paused_func_user_data(void* on_gameplay_paused_func_user_data)
{
   this->on_gameplay_paused_func_user_data = on_gameplay_paused_func_user_data;
}


void Standard::set_on_gameplay_unpaused_func(std::function<void(AllegroFlare::Routers::Standard*, void*)> on_gameplay_unpaused_func)
{
   this->on_gameplay_unpaused_func = on_gameplay_unpaused_func;
}


void Standard::set_on_gameplay_unpaused_func_user_data(void* on_gameplay_unpaused_func_user_data)
{
   this->on_gameplay_unpaused_func_user_data = on_gameplay_unpaused_func_user_data;
}


void Standard::set_on_primary_gameplay_screen_finished_func(std::function<void(AllegroFlare::Routers::Standard*, void*)> on_primary_gameplay_screen_finished_func)
{
   this->on_primary_gameplay_screen_finished_func = on_primary_gameplay_screen_finished_func;
}


void Standard::set_on_primary_gameplay_screen_finished_func_user_data(void* on_primary_gameplay_screen_finished_func_user_data)
{
   this->on_primary_gameplay_screen_finished_func_user_data = on_primary_gameplay_screen_finished_func_user_data;
}


void Standard::set_on_arbitrary_storyboard_screen_finished_func(std::function<void(AllegroFlare::Routers::Standard*, void*)> on_arbitrary_storyboard_screen_finished_func)
{
   this->on_arbitrary_storyboard_screen_finished_func = on_arbitrary_storyboard_screen_finished_func;
}


void Standard::set_on_arbitrary_storyboard_screen_finished_func_user_data(void* on_arbitrary_storyboard_screen_finished_func_user_data)
{
   this->on_arbitrary_storyboard_screen_finished_func_user_data = on_arbitrary_storyboard_screen_finished_func_user_data;
}


void Standard::set_on_arbitrary_storyboard_screen_activated_func(std::function<void(AllegroFlare::Routers::Standard*, void*)> on_arbitrary_storyboard_screen_activated_func)
{
   this->on_arbitrary_storyboard_screen_activated_func = on_arbitrary_storyboard_screen_activated_func;
}


void Standard::set_on_arbitrary_storyboard_screen_activated_func_user_data(void* on_arbitrary_storyboard_screen_activated_func_user_data)
{
   this->on_arbitrary_storyboard_screen_activated_func_user_data = on_arbitrary_storyboard_screen_activated_func_user_data;
}


AllegroFlare::EventEmitter* Standard::get_event_emitter() const
{
   return event_emitter;
}


std::function<bool(AllegroFlare::RouteEventDatas::Base*)> Standard::get_load_level_handler() const
{
   return load_level_handler;
}


std::function<bool(uint32_t, AllegroFlare::Routers::Standard*, void*)> Standard::get_on_route_event_unhandled_func() const
{
   return on_route_event_unhandled_func;
}


void* Standard::get_on_route_event_unhandled_func_user_data() const
{
   return on_route_event_unhandled_func_user_data;
}


std::function<void(AllegroFlare::Routers::Standard*, void*)> Standard::get_on_load_last_played_session_or_start_new_func() const
{
   return on_load_last_played_session_or_start_new_func;
}


void* Standard::get_on_load_last_played_session_or_start_new_func_user_data() const
{
   return on_load_last_played_session_or_start_new_func_user_data;
}


std::function<void(AllegroFlare::Routers::Standard*, void*)> Standard::get_on_create_new_session_func() const
{
   return on_create_new_session_func;
}


void* Standard::get_on_create_new_session_func_user_data() const
{
   return on_create_new_session_func_user_data;
}


std::function<void(AllegroFlare::Routers::Standard*, void*)> Standard::get_on_continue_from_last_save_func() const
{
   return on_continue_from_last_save_func;
}


void* Standard::get_on_continue_from_last_save_func_user_data() const
{
   return on_continue_from_last_save_func_user_data;
}


std::function<void(AllegroFlare::Routers::Standard*, void*)> Standard::get_on_load_save_file_content_into_gameplay_func() const
{
   return on_load_save_file_content_into_gameplay_func;
}


void* Standard::get_on_load_save_file_content_into_gameplay_func_user_data() const
{
   return on_load_save_file_content_into_gameplay_func_user_data;
}


std::function<void(AllegroFlare::Routers::Standard*, void*)> Standard::get_on_gameplay_paused_func() const
{
   return on_gameplay_paused_func;
}


void* Standard::get_on_gameplay_paused_func_user_data() const
{
   return on_gameplay_paused_func_user_data;
}


std::function<void(AllegroFlare::Routers::Standard*, void*)> Standard::get_on_gameplay_unpaused_func() const
{
   return on_gameplay_unpaused_func;
}


void* Standard::get_on_gameplay_unpaused_func_user_data() const
{
   return on_gameplay_unpaused_func_user_data;
}


std::function<void(AllegroFlare::Routers::Standard*, void*)> Standard::get_on_primary_gameplay_screen_finished_func() const
{
   return on_primary_gameplay_screen_finished_func;
}


void* Standard::get_on_primary_gameplay_screen_finished_func_user_data() const
{
   return on_primary_gameplay_screen_finished_func_user_data;
}


std::function<void(AllegroFlare::Routers::Standard*, void*)> Standard::get_on_arbitrary_storyboard_screen_finished_func() const
{
   return on_arbitrary_storyboard_screen_finished_func;
}


void* Standard::get_on_arbitrary_storyboard_screen_finished_func_user_data() const
{
   return on_arbitrary_storyboard_screen_finished_func_user_data;
}


std::function<void(AllegroFlare::Routers::Standard*, void*)> Standard::get_on_arbitrary_storyboard_screen_activated_func() const
{
   return on_arbitrary_storyboard_screen_activated_func;
}


void* Standard::get_on_arbitrary_storyboard_screen_activated_func_user_data() const
{
   return on_arbitrary_storyboard_screen_activated_func_user_data;
}


AllegroFlare::GameSession &Standard::get_game_session_ref()
{
   return game_session;
}


void Standard::emit_route_event(uint32_t route_event, AllegroFlare::RouteEventDatas::Base* route_event_data, float time_now)
{
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Routers::Standard::emit_route_event]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Routers::Standard::emit_route_event]: error: guard \"event_emitter\" not met");
   }
   event_emitter->emit_router_event(route_event, route_event_data, time_now);
   return;
}

void Standard::suspend_accumulating_playtime()
{
   if (!(game_session.is_active()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Routers::Standard::suspend_accumulating_playtime]: error: guard \"game_session.is_active()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Routers::Standard::suspend_accumulating_playtime]: error: guard \"game_session.is_active()\" not met");
   }
   game_session.get_playtime_tracker_ref().pause();
   return;
}

void Standard::start_or_resume_accumulating_playtime()
{
   if (!(game_session.is_active()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Routers::Standard::start_or_resume_accumulating_playtime]: error: guard \"game_session.is_active()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Routers::Standard::start_or_resume_accumulating_playtime]: error: guard \"game_session.is_active()\" not met");
   }
   game_session.get_playtime_tracker_ref().start();
   return;
}

std::string Standard::name_for_route_event(uint32_t route_event)
{
   static const std::unordered_map<uint32_t, std::string> event_names {
      {EVENT_UNDEFINED, "EVENT_UNDEFINED"},
      {EVENT_INITIALIZE, "EVENT_INITIALIZE"},
      {EVENT_EXIT_GAME, "EVENT_EXIT_GAME"},
      {EVENT_START_NEW_GAME, "EVENT_START_NEW_GAME"},
      {EVENT_CONTINUE_FROM_LAST_SAVE, "EVENT_CONTINUE_FROM_LAST_SAVE"},
      {EVENT_LOAD_A_SAVED_GAME, "EVENT_LOAD_A_SAVED_GAME" },
      {EVENT_SAVE_GAME, "EVENT_SAVE_GAME"},
      {EVENT_PAUSE_GAME, "EVENT_PAUSE_GAME"},
      {EVENT_UNPAUSE_GAME, "EVENT_UNPAUSE_GAME"},
      {EVENT_WIN_GAME, "EVENT_WIN_GAME"},
      {EVENT_LOSE_GAME, "EVENT_LOSE_GAME"},
      {EVENT_START_LEVEL, "EVENT_START_LEVEL"},
      {EVENT_EXIT_TO_TITLE_SCREEN, "EVENT_EXIT_TO_TITLE_SCREEN"},
      {EVENT_INTRO_LOGOS_SCREEN_FINISHED, "EVENT_INTRO_LOGOS_SCREEN_FINISHED"},
      {EVENT_INTRO_STORYBOARD_SCREEN_FINISHED, "EVENT_INTRO_STORYBOARD_SCREEN_FINISHED"},
      {EVENT_NEW_GAME_INTRO_STORYBOARD_SCREEN_FINISHED, "EVENT_NEW_GAME_INTRO_STORYBOARD_SCREEN_FINISHED"},
      {EVENT_PRIMARY_GAMEPLAY_SCREEN_FINISHED, "EVENT_PRIMARY_GAMEPLAY_SCREEN_FINISHED"},
      {EVENT_ARBITRARY_STORYBOARD_SCREEN_FINISHED, "EVENT_ARBITRARY_STORYBOARD_SCREEN_FINISHED"},
      {EVENT_GAME_WON_OUTRO_STORYBOARD_SCREEN_FINISHED, "EVENT_GAME_WON_OUTRO_STORYBOARD_SCREEN_FINISHED"},
      {EVENT_CREDITS_SCREEN_FINISHED, "EVENT_CREDITS_SCREEN_FINISHED"},
      {EVENT_TITLE_SCREEN_FINISHED, "EVENT_TITLE_SCREEN_FINISHED"},
      {EVENT_SUSPEND_ACCUMULATING_PLAYTIME, "EVENT_SUSPEND_ACCUMULATING_PLAYTIME" },
      {EVENT_START_OR_RESUME_ACCUMULATING_PLAYTIME, "EVENT_START_OR_RESUME_ACCUMULATING_PLAYTIME" },
      {EVENT_ACTIVATE_INTRO_LOGOS_SCREEN, "EVENT_ACTIVATE_INTRO_LOGOS_SCREEN"},
      {EVENT_ACTIVATE_INTRO_STORYBOARD_SCREEN, "EVENT_ACTIVATE_INTRO_STORYBOARD_SCREEN"},
      {EVENT_ACTIVATE_TITLE_SCREEN, "EVENT_ACTIVATE_TITLE_SCREEN"},
      {EVENT_ACTIVATE_ACHIEVEMENTS_SCREEN, "EVENT_ACTIVATE_ACHIEVEMENTS_SCREEN"},
      {EVENT_ACTIVATE_CHARACTER_NAME_INPUT_SCREEN, "EVENT_CHARACTER_NAME_INPUT_SCREEN"},
      {EVENT_ACTIVATE_DISPLAY_SETTINGS_SCREEN, "EVENT_ACTIVATE_DISPLAY_SETTINGS_SCREEN"},
      {EVENT_ACTIVATE_SETTINGS_SCREEN, "EVENT_ACTIVATE_SETTINGS_SCREEN"},
      {EVENT_ACTIVATE_VERSION_SCREEN, "EVENT_ACTIVATE_VERSION_SCREEN"},
      {EVENT_ACTIVATE_NEW_GAME_INTRO_STORYBOARD_SCREEN, "EVENT_ACTIVATE_NEW_GAME_INTRO_STORYBOARD_SCREEN"},
      {EVENT_ACTIVATE_LEVEL_SELECT_SCREEN, "EVENT_ACTIVATE_LEVEL_SELECT_SCREEN"},
      {EVENT_ACTIVATE_ARBITRARY_STORYBOARD_SCREEN, "EVENT_ACTIVATE_ARBITRARY_STORYBOARD_SCREEN"},
      {EVENT_ACTIVATE_GAME_OVER_SCREEN, "EVENT_ACTIVATE_GAME_OVER_SCREEN"},
      {EVENT_ACTIVATE_GAME_WON_SCREEN, "EVENT_ACTIVATE_GAME_WON_SCREEN"},
      {EVENT_ACTIVATE_GAME_WON_OUTRO_STORYBOARD_SCREEN, "EVENT_ACTIVATE_GAME_WON_OUTRO_STORYBOARD_SCREEN"},
      {EVENT_ACTIVATE_CREDITS_SCREEN, "EVENT_ACTIVATE_CREDITS_SCREEN"},
      {EVENT_ACTIVATE_PRIMARY_GAMEPLAY_SCREEN, "EVENT_ACTIVATE_PRIMARY_GAMEPLAY_SCREEN"},
      {EVENT_ACTIVATE_PRIMARY_GAMEPLAY_SUBSCREEN, "EVENT_ACTIVATE_PRIMARY_GAMEPLAY_SUBSCREEN"},
      {EVENT_ACTIVATE_PAUSE_SCREEN, "EVENT_ACTIVATE_PAUSE_SCREEN"}
   };

   auto it = event_names.find(route_event);

   if (it == event_names.end())
   {
      return "UNKNOWN_EVENT";
   }
   else
   {
      return it->second;
   }
}

void Standard::on_route_event(uint32_t route_event, AllegroFlare::RouteEventDatas::Base* route_event_data, float time_now)
{
   if (!((route_event != EVENT_UNDEFINED)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Routers::Standard::on_route_event]: error: guard \"(route_event != EVENT_UNDEFINED)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Routers::Standard::on_route_event]: error: guard \"(route_event != EVENT_UNDEFINED)\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Routers::Standard::on_route_event]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Routers::Standard::on_route_event]: error: guard \"event_emitter\" not met");
   }
   AllegroFlare::Logger::info_from(
      "AllegroFlare::Routers::Standard::on_route_event",
      "Route Event: " + name_for_route_event(route_event) + " (" + std::to_string(route_event) + ")"
   );

   std::map<uint32_t, std::function<void()>> event_map = {

      // System Events

      { EVENT_INITIALIZE, [this](){
         // TODO: Consider different initial route depending on deployment environment
         // TODO: Consider guard on event when a session is already active (e.g. already initialized)

         // TODO: Test this method callback
         if (on_load_last_played_session_or_start_new_func)
         {
            // TODO: Consider if this should return a boolean on success
            // As a convenience, attempt to load the game session that was running the last time the game was
            // played
            on_load_last_played_session_or_start_new_func(
               this,
               on_load_last_played_session_or_start_new_func_user_data
            );
         }
         else
         {
            // TODO: Add boolean option to remove this warning
            AllegroFlare::Logger::warn_from(
               "AllegroFlare::Routers::Standard::on_route_event",
               "on EVENT_INITIALIZE, expecting an \"on_load_last_played_session_or_start_new_func\" to be present, "
                  "but it is not."
            );
         }
         game_session.start_session();

         emit_route_event(EVENT_ACTIVATE_INTRO_LOGOS_SCREEN);
      }},
      { EVENT_EXIT_GAME, [this](){
         // End the session if active
         if (game_session.is_active()) game_session.end_session();

         // Emit an event to exit the game
         event_emitter->emit_exit_game_event();
      }},


      // Game Events

      { EVENT_START_NEW_GAME, [this](){
         // Start new session
         if (game_session.is_active())
         {
            // TODO: Consider a confirmation dialog somewhere, e.g. "Would you like to save existing progress before
            // starting a new game?"
            game_session.end_session();
         }

         // TODO: Test this method callback
         if (on_create_new_session_func)
         {
            // TODO: Consider if this should return a boolean on success
            on_create_new_session_func(this, on_create_new_session_func_user_data);
         }
         else
         {
            // TODO: Add boolean option to remove this warning
            AllegroFlare::Logger::warn_from(
               "AllegroFlare::Routers::Standard::on_route_event",
               "on EVENT_START_NEW_GAME, expecting an \"on_create_new_session_func\" to be present, "
                  "but it is not."
            );
         }
         game_session.start_session();

         // Start the intro storyboard
         emit_route_event(EVENT_ACTIVATE_NEW_GAME_INTRO_STORYBOARD_SCREEN);
      }},
      { EVENT_CONTINUE_FROM_LAST_SAVE, [this](){
         // TODO: Finish the actions in this event
         // Event data: game session id

         // restore session
         // TODO: game_session.continue_session();

         // activate gameplay_screen

         // TODO: Test this callback
         if (on_continue_from_last_save_func)
         {
            // TODO: Consider if this should return a boolean on success
            on_continue_from_last_save_func(this, on_continue_from_last_save_func_user_data);
         }
         else
         {
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::Routers::Standard::on_route_event",
               "on EVENT_CONTINUE_FROM_LAST_SAVE, expecting an \"on_continue_from_last_save_func\" to be present, "
                  "but it is not."
            );
         }
         // TODO: Implement an callback on this event
      }},
      { EVENT_LOAD_A_SAVED_GAME, [this](){
         // TODO: Test this callback
         if (on_load_save_file_content_into_gameplay_func)
         {
            on_load_save_file_content_into_gameplay_func(
               this,
               on_load_save_file_content_into_gameplay_func_user_data
            );
         }
         else
         {
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::Routers::Standard::on_route_event",
               "on EVENT_LOAD_A_SAVED_GAME, expecting an \"on_load_save_file_content_into_gameplay_func\" to be "
                  "present, but it is not."
            );
         }
      }},
      { EVENT_WIN_GAME, [this](){
         // TODO: Finish the actions in this event

         // Validate an active session
         if (!game_session.is_active())
         {
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::Routers::Standard::on_route_event",
               "When handling an EVENT_WIN_GAME, the game_session is expected to be active but it was not."
            );
         }

         // End the session
         game_session.end_session();

         // Activate game won outro
         emit_route_event(EVENT_ACTIVATE_GAME_WON_OUTRO_STORYBOARD_SCREEN);
      }},
      { EVENT_LOSE_GAME, [this](){
         // TODO: Finish the actions in this event
         // Validate an active session
         if (!game_session.is_active())
         {
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::Routers::Standard::on_route_event",
               "When handling an EVENT_LOSE_GAME, the game_session is expected to be active but it was not."
            );
         }

         // End the session
         game_session.end_session();

         // Activate the game_over_screen
         emit_route_event(EVENT_ACTIVATE_GAME_OVER_SCREEN);
      }},
      { EVENT_START_LEVEL, [this, route_event_data](){
         // TODO: Finish the actions in this event
         // TODO: Consider Validating an active session
         // TODO: Consider alternative to route_event_data that includes some "level to load" info
         // TODO: Consider boolean result for "load_level_handler", return to title screen if false is returned
         if (!load_level_handler)
         {
            AllegroFlare::Logger::warn_from(
               "AllegroFlare::Routers::Standard::on_route_event",
               "When handling EVENT_START_LEVEL, the load_level_handler was not preesnt. If this is expected "
                 "behavior and you do not wish to see this warning, please code in a flag to inhibit this message."
            );
         }
         else
         {
            bool level_load_was_successful = false;
            level_load_was_successful = load_level_handler(route_event_data);
            if (!level_load_was_successful)
            {
               AllegroFlare::Logger::throw_error(
                  "AllegroFlare::Routers::Standard::on_route_event",
                  "When handling EVENT_START_LEVEL, the level load was not successful (it returned false "
                     "when called)."
               );
            }
            else
            {
               emit_route_event(EVENT_ACTIVATE_PRIMARY_GAMEPLAY_SCREEN);
            }
         }
      }},
      { EVENT_SAVE_GAME, [this](){
         if (!game_session.is_active())
         {
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::Routers::Standard::on_route_event",
               "When handling EVENT_SAVE_GAME, the game session is not currently active."
            );
         }

         // TODO: Add info log here?
         AllegroFlare::Logger::throw_error(THIS_CLASS_AND_METHOD_NAME, "Saving game...");
         game_session.save();
         AllegroFlare::Logger::throw_error(THIS_CLASS_AND_METHOD_NAME, "...game saved successfully.");
      }},
      { EVENT_PAUSE_GAME, [this](){
         // TODO: Test playtime is paused on this event
         // TODO: Consider if game time spent in the pause screen (on the map screen? on inventory changes, etc?)
         // should be counted towards accumulated play time or not.
         //suspend_accumulating_playtime();

         // Call the callback
         // TODO: Test this conditional
         if (!on_gameplay_paused_func)
         {
            // TODO: Test this warning message
            AllegroFlare::Logger::warn_from_once(
               "AllegroFlare::Routers::Standard::on_route_event",
               "Handling a EVENT_PAUSE_GAME but no \"on_gameplay_paused_func\" callback is present. Usually you "
                  "would use this callback to make changes to your system's state (e.g. activate a subscreen "
                  "or a pause screen)."
            );
         }
         else
         {
            // Call the callback
            on_gameplay_paused_func(this, on_gameplay_paused_func_user_data); // TODO: Test this
         }
      }},
      { EVENT_UNPAUSE_GAME, [this](){
         // TODO: Test this conditional
         if (!on_gameplay_unpaused_func)
         {
            // TODO: Test this warning message
            AllegroFlare::Logger::warn_from_once(
               "AllegroFlare::Routers::Standard::on_route_event",
               "Handling a EVENT_UNPAUSE_GAME but no \"on_gameplay_unpaused_func\" callback is present. Usually "
                  "you would use this callback to make changes to your system's state (e.g. re-activate gameplay "
                  "screen if it was deactivated in the \"on_gameplay_paused_func\" callback)."
            );
         }
         else
         {
            // Call the callback
            on_gameplay_unpaused_func(this, on_gameplay_unpaused_func_user_data); // TODO: Test this
         }

         // TODO: Test playtime is resumed on this event
         // TODO: Consider if game time spent in the pause screen (on the map screen? on inventory changes, etc?)
         // should be counted towards accumulated play time or not.
         // NOTE: For now, this has been moved up into the game configuration
         //start_or_resume_accumulating_playtime();
      }},
      { EVENT_EXIT_TO_TITLE_SCREEN, [this](){
         // Validate an active session
         if (!game_session.is_active())
         {
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::Routers::Standard::on_route_event",
               "When handling an EVENT_EXIT_TO_TITLE_SCREEN, the game_session is expected to be active but it "
                  "was not."
            );
         }

         // End the session
         game_session.end_session();

         // Activate title_screen
         emit_route_event(EVENT_ACTIVATE_TITLE_SCREEN);
      }},


      // Suspend and resume playtime
      { EVENT_SUSPEND_ACCUMULATING_PLAYTIME, [this](){
         suspend_accumulating_playtime();
      }},
      { EVENT_START_OR_RESUME_ACCUMULATING_PLAYTIME, [this](){
         start_or_resume_accumulating_playtime();
      }},

      // Screens finished events

      { EVENT_INTRO_LOGOS_SCREEN_FINISHED, [this](){
         emit_route_event(EVENT_ACTIVATE_INTRO_STORYBOARD_SCREEN);
      }},
      { EVENT_INTRO_STORYBOARD_SCREEN_FINISHED, [this](){
         emit_route_event(EVENT_ACTIVATE_TITLE_SCREEN);
      }},
      { EVENT_NEW_GAME_INTRO_STORYBOARD_SCREEN_FINISHED, [this](){
         emit_route_event(EVENT_ACTIVATE_LEVEL_SELECT_SCREEN);
      }},
      { EVENT_PRIMARY_GAMEPLAY_SCREEN_FINISHED, [this](){
         if (on_primary_gameplay_screen_finished_func)
         {
            // TODO: Consider if this should return a boolean on success
            on_primary_gameplay_screen_finished_func(this, on_primary_gameplay_screen_finished_func_user_data);
         }
         else
         {
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::Routers::Standard::on_route_event",
               "on EVENT_PRIMARY_GAMEPLAY_SCREEN_FINISHED, expecting an "
                  "\"on_primary_gameplay_screen_finished_func\" to be present, but it is not."
            );
         }
      }},
      { EVENT_ARBITRARY_STORYBOARD_SCREEN_FINISHED, [this](){
         if (on_arbitrary_storyboard_screen_finished_func)
         {
            // TODO: Consider if this should return a boolean on success
            on_arbitrary_storyboard_screen_finished_func(
                  this,
                  on_arbitrary_storyboard_screen_finished_func_user_data
               );
         }
         else
         {
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::Routers::Standard::on_route_event",
               "on EVENT_ARBITRARY_STORYBOARD_SCREEN_FINISHED, expecting an "
                  "\"on_arbitrary_storyboard_screen_finished_func\" to be present, but it is not."
            );
         }
      }},
      { EVENT_GAME_WON_OUTRO_STORYBOARD_SCREEN_FINISHED, [this](){
         emit_route_event(EVENT_ACTIVATE_CREDITS_SCREEN);
      }},
      { EVENT_CREDITS_SCREEN_FINISHED, [this](){
         emit_route_event(EVENT_ACTIVATE_GAME_WON_SCREEN);
      }},
      { EVENT_TITLE_SCREEN_FINISHED, [this](){
         // NOTE: This is a loop to restart the intro(s) so the game is not stuck on title screen
         emit_route_event(EVENT_ACTIVATE_INTRO_LOGOS_SCREEN);
      }},


      // Activate Screens

      { EVENT_ACTIVATE_INTRO_LOGOS_SCREEN, [this](){
         activate_screen(INTRO_LOGOS_SCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_INTRO_STORYBOARD_SCREEN, [this](){
         activate_screen(INTRO_STORYBOARD_SCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_TITLE_SCREEN, [this](){
         activate_screen(TITLE_SCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_ACHIEVEMENTS_SCREEN, [this](){
         activate_screen(ACHIEVEMENTS_SCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_DISPLAY_SETTINGS_SCREEN, [this](){
         activate_screen(DISPLAY_SETTINGS_SCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_SETTINGS_SCREEN, [this](){
         activate_screen(SETTINGS_SCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_VERSION_SCREEN, [this](){
         activate_screen(VERSION_SCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_LOAD_A_SAVED_GAME_SCREEN, [this](){
         activate_screen(LOAD_A_SAVED_GAME_SCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_NEW_GAME_INTRO_STORYBOARD_SCREEN, [this](){
         activate_screen(NEW_GAME_INTRO_STORYBOARD_SCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_LEVEL_SELECT_SCREEN, [this](){
         // TODO: Consider a special case here to "skip" directly to next step if the level select screen is empty
         // or auto-advances. I think this most likely will be a callback with a value returned.
         activate_screen(LEVEL_SELECT_SCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_GAME_OVER_SCREEN, [this](){
         activate_screen(GAME_OVER_SCREEN_IDENTIFIER);
      }},
      // TODO: Test this emit reaction
      { EVENT_ACTIVATE_CHARACTER_NAME_INPUT_SCREEN, [this](){
         activate_screen(CHARACTER_NAME_INPUT_SCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_GAME_WON_SCREEN, [this](){
         activate_screen(GAME_WON_SCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_GAME_WON_OUTRO_STORYBOARD_SCREEN, [this](){
         activate_screen(GAME_WON_OUTRO_STORYBOARD_SCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_ARBITRARY_STORYBOARD_SCREEN, [this, route_event_data](){
         (void)(route_event_data); // TODO: See if this argument should just be removed
         if (on_arbitrary_storyboard_screen_activated_func)
         {
            // TODO: Consider if this should return a boolean on success
            // NOTE: Note this callback occurs *before* the screen is activated
            // NOTE: Typically this callback is used to load the storyboard (given data passed in through user_data).
            on_arbitrary_storyboard_screen_activated_func(
                  this,
                  on_arbitrary_storyboard_screen_activated_func_user_data
               );
         }
         else
         {
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::Routers::Standard::on_route_event",
               "on EVENT_ACTIVATE_ARBITRARY_STORYBOARD_SCREEN, expecting an "
                  "\"on_arbitrary_storyboard_screen_activated_func\" to be present, but it is not."
            );
         }

         activate_screen(ARBITRARY_STORYBOARD_SCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_CREDITS_SCREEN, [this](){
         activate_screen(CREDITS_SCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_PRIMARY_GAMEPLAY_SCREEN, [this](){
         activate_screen(PRIMARY_GAMEPLAY_SCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_PRIMARY_GAMEPLAY_SUBSCREEN, [this](){
         activate_screen(PRIMARY_GAMEPLAY_SUBSCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_PAUSE_SCREEN, [this](){
         activate_screen(PAUSE_SCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_SCREEN_BY_IDENTIFIER, [this, route_event_data](){
         (void)(route_event_data); // TODO: See if this argument should just be removed
         // TODO: Test this event

         // TODO: Test this condition
         if (!route_event_data)
         {
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::Routers::Standard::on_route_event",
               "Unable to handle event of type EVENT_ACTIVATE_SCREEN_BY_IDENTIFIER because \"route_event_data\" is "
                  "a nullptr."
            );
         }
         // TODO: Test this condition
         if (!route_event_data->is_type(AllegroFlare::RouteEventDatas::ActivateScreenByIdentifier::TYPE))
         {
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::Routers::Standard::on_route_event",
               "Unable to handle event of type EVENT_ACTIVATE_SCREEN_BY_IDENTIFIER because \"route_event_data\" is "
                  "not the expected type AllegroFlare::RouteEventDatas::ActivateScreenByIdentifier::TYPE."
            );
         }

         AllegroFlare::RouteEventDatas::ActivateScreenByIdentifier *as_activate_screen_by_identifier =
            static_cast<AllegroFlare::RouteEventDatas::ActivateScreenByIdentifier*>(route_event_data);

         std::string screen_identifier = as_activate_screen_by_identifier->get_screen_identifier();
         activate_screen(screen_identifier);
      }},
   };

   // Locate and call the function to handle the event
   if (event_map.count(route_event) == 0)
   {
      if (on_route_event_unhandled_func)
      {
         bool callback_result_successful =
            on_route_event_unhandled_func(route_event, this, on_route_event_unhandled_func_user_data);

         if (!callback_result_successful)
         {
            AllegroFlare::Logger::throw_error(
                  "AllegroFlare::Routers::Standard::on_route_event",
                  "A user callback was used to handle an unknown event of type " + std::to_string(route_event) + ", "
                     "but the callback returned false, indicating that there was a failure to handle the event."
               );
         }
      }
      else
      {
         // event not found
         AllegroFlare::Logger::throw_error(
               "AllegroFlare::Routers::Standard::on_route_event",
               "Unable to handle event of type " + std::to_string(route_event) + "."
            );
      }
   }
   else
   {
      // call the event
      event_map[route_event]();
   }

   return;
}


} // namespace Routers
} // namespace AllegroFlare


