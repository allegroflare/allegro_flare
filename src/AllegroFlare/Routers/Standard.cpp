

#include <AllegroFlare/Routers/Standard.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Routers
{


Standard::Standard(AllegroFlare::EventEmitter* event_emitter)
   : AllegroFlare::Routers::Base(AllegroFlare::Routers::Standard::TYPE)
   , event_emitter(event_emitter)
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


AllegroFlare::EventEmitter* Standard::get_event_emitter() const
{
   return event_emitter;
}


AllegroFlare::GameSession &Standard::get_game_session_ref()
{
   return game_session;
}


void Standard::emit_route_event(uint32_t route_event)
{
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[Standard::emit_route_event]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Standard::emit_route_event: error: guard \"event_emitter\" not met");
   }
   event_emitter->emit_router_event(route_event);
   return;
}

void Standard::on_route_event(uint32_t route_event)
{
   if (!((route_event != 0)))
   {
      std::stringstream error_message;
      error_message << "[Standard::on_route_event]: error: guard \"(route_event != 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Standard::on_route_event: error: guard \"(route_event != 0)\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[Standard::on_route_event]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Standard::on_route_event: error: guard \"event_emitter\" not met");
   }

   //std::string route_event = ev->get_type();
   std::cout << "Route event emitted: \"" << route_event << "\"" << std::endl;

   std::map<uint32_t, std::function<void()>> event_map = {

      // System Events

      { EVENT_INITIALIZE, [this](){
         // TODO: Consider different initial route depending on deployment environment
         emit_route_event(EVENT_ACTIVATE_INTRO_LOGOS_SCREEN);
      }},
      { EVENT_EXIT_GAME, [this](){
         // close session

         if (game_session.is_active()) game_session.end_session();
         // TODO: abort = true;
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
         // TODO: Validate session active
         // stop session
         game_session.end_session();
         // activate game_won_outro_storyboards_screen
      }},
      { EVENT_LOSE_GAME, [this](){
         // TODO: Finish the actions in this event
         // TODO: Validate session active
         // stop session
         game_session.end_session();
         // activate game_over_screen
      }},
      { EVENT_START_LEVEL, [this](){
         // TODO: Finish the actions in this event
         // Event data: level info
         // primary_gameplay_screen-> load level
         // activate primary_gameplay_screen
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
         // stop session
         // activate title_screen
      }},


      // Screens finished events

      { EVENT_INTRO_LOGOS_INISHED, [this](){
         // TODO
      }},
      { EVENT_INTRO_STORYBOARDS_FINISHED, [this](){
         // TODO
      }},
      { EVENT_NEW_GAME_INTRO_STORYBOARDS_FINISHED, [this](){
         // TODO
      }},
      { EVENT_GAME_WON_OUTRO_STORYBOARDS_FINISHED, [this](){
         // TODO
      }},
      { EVENT_CREDITS_SCREEN_FINISHED, [this](){
         // TODO
      }},
      { EVENT_TITLE_SCREEN_TIMEOUT, [this](){
         // TODO
      }},


      // Activate Screens

      { EVENT_ACTIVATE_INTRO_LOGOS_SCREEN, [this](){
         activate_screen(INTRO_LOGOS_SCREEN_IDENTIFIER);
      }},
      { EVENT_ACTIVATE_INTRO_STORYBOARDS_SCREEN, [this](){
         activate_screen(INTRO_STORYBOARDS_SCREEN_IDENTIFIER);
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
      std::cout << "ERROR: event not found: \"" << route_event << "\"" << std::endl;
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


