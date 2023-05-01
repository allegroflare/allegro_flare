

#include <AllegroFlare/Routers/Standard.hpp>

#include <AllegroFlare/Logger.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Routers
{


Standard::Standard(AllegroFlare::EventEmitter* event_emitter, std::function<void(AllegroFlare::RouteEventDatas::Base*)> load_level_event_handler)
   : AllegroFlare::Routers::Base(AllegroFlare::Routers::Standard::TYPE)
   , event_emitter(event_emitter)
   , load_level_event_handler(load_level_event_handler)
   , game_session()
{
}


Standard::~Standard()
{
}


void Standard::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void Standard::set_load_level_event_handler(std::function<void(AllegroFlare::RouteEventDatas::Base*)> load_level_event_handler)
{
   this->load_level_event_handler = load_level_event_handler;
}


AllegroFlare::EventEmitter* Standard::get_event_emitter() const
{
   return event_emitter;
}


std::function<void(AllegroFlare::RouteEventDatas::Base*)> Standard::get_load_level_event_handler() const
{
   return load_level_event_handler;
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
      error_message << "[Standard::emit_route_event]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Standard::emit_route_event: error: guard \"event_emitter\" not met");
   }
   event_emitter->emit_router_event(route_event, route_event_data, time_now);
   return;
}

void Standard::on_route_event(uint32_t route_event, AllegroFlare::RouteEventDatas::Base* route_event_data, float time_now)
{
   if (!((route_event != EVENT_UNDEFINED)))
   {
      std::stringstream error_message;
      error_message << "[Standard::on_route_event]: error: guard \"(route_event != EVENT_UNDEFINED)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Standard::on_route_event: error: guard \"(route_event != EVENT_UNDEFINED)\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[Standard::on_route_event]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Standard::on_route_event: error: guard \"event_emitter\" not met");
   }
   std::map<uint32_t, std::function<void()>> event_map = {

      // System Events

      { EVENT_INITIALIZE, [this](){
         // TODO: Consider different initial route depending on deployment environment
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
         // start new session
         game_session.start_session();

         // activate new_game_intro_storyboards
         emit_route_event(EVENT_ACTIVATE_NEW_GAME_INTRO_STORYBOARD_SCREEN);
      }},
      { EVENT_CONTINUE_A_SAVED_GAME, [this](){
         // TODO: Finish the actions in this event
         // Event data: game session id

         // restore session
         // TODO: game_session.continue_session();

         // activate gameplay_screen
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
         // Validate an active session
         // Event data: level info
         // TODO: Consider alternative to route_event_data structure might need to be passed
         // TODO: Test this function call
         if (load_level_event_handler) load_level_event_handler(route_event_data);

         // TODO: Test this emitted event
         emit_route_event(EVENT_ACTIVATE_PRIMARY_GAMEPLAY_SCREEN);
      }},
      //{ EVENT_PAUSE_GAME, [this](){
         // TODO: Finish the actions in this event
         // guard: not already pause screen
         // pause session?
         //screen_identifier_before_pause = get_framework()->get_currently_active_screen_name();
         // capture "pre-pause screen"
         // activate pause_screen
      //}},
      //{ EVENT_UNPAUSE_GAME, [this](){
         // TODO: Finish the actions in this event
         // guard: is paused
         // unpause session?

         // activate "pre-pause screen"
         //activate_screen(screen_identifier_before_pause);
      //}},
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


      // Screens finished events

      { EVENT_INTRO_LOGOS_SCREEN_FINISHED, [this](){
         emit_route_event(EVENT_ACTIVATE_NEW_GAME_INTRO_STORYBOARD_SCREEN);
      }},
      { EVENT_INTRO_STORYBOARD_SCREEN_FINISHED, [this](){
         emit_route_event(EVENT_ACTIVATE_TITLE_SCREEN);
      }},
      { EVENT_NEW_GAME_INTRO_STORYBOARD_SCREEN_FINISHED, [this](){
         emit_route_event(EVENT_ACTIVATE_LEVEL_SELECT_SCREEN);
      }},
      { EVENT_GAME_WON_OUTRO_STORYBOARD_SCREEN_FINISHED, [this](){
         emit_route_event(EVENT_ACTIVATE_CREDITS_SCREEN);
      }},
      { EVENT_CREDITS_SCREEN_FINISHED, [this](){
         emit_route_event(EVENT_ACTIVATE_GAME_WON_SCREEN);
      }},
      { EVENT_TITLE_SCREEN_FINISHED, [this](){
         // This is a loop to restart the intro(s) so the game is not stuck on title screen
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
      { EVENT_ACTIVATE_SETTINGS_SCREEN, [this](){
         activate_screen(SETTINGS_SCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_VERSION_SCREEN, [this](){
         activate_screen(VERSION_SCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_NEW_GAME_INTRO_STORYBOARD_SCREEN, [this](){
         activate_screen(NEW_GAME_INTRO_STORYBOARD_SCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_LEVEL_SELECT_SCREEN, [this](){
         activate_screen(LEVEL_SELECT_SCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_GAME_OVER_SCREEN, [this](){
         activate_screen(GAME_OVER_SCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_GAME_WON_SCREEN, [this](){
         activate_screen(GAME_WON_SCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_GAME_WON_OUTRO_STORYBOARD_SCREEN, [this](){
         activate_screen(GAME_WON_OUTRO_STORYBOARD_SCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_CREDITS_SCREEN, [this](){
         activate_screen(CREDITS_SCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_PRIMARY_GAMEPLAY_SCREEN, [this](){
         activate_screen(PRIMARY_GAMEPLAY_SCREEN_IDENTIFIER);
      }},
   };

   // locate and call the function to handle the event
   if (event_map.count(route_event) == 0)
   {
      // event not found
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Routers::Standard::on_route_event",
         "Unable to handle event of type " + std::to_string(route_event) + "."
      );
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


