

#include <AllegroFlare/Routers/Standard.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Routers
{


Standard::Standard(AllegroFlare::GameSession** game_session)
   : AllegroFlare::Routers::Base(AllegroFlare::Routers::Standard::TYPE)
   , game_session(game_session)
{
}


Standard::~Standard()
{
}


void Standard::set_game_session(AllegroFlare::GameSession** game_session)
{
   this->game_session = game_session;
}


AllegroFlare::GameSession** Standard::get_game_session() const
{
   return game_session;
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
         // TODO: abort = true;
      }},


      // Game Events

      { EVENT_START_NEW_GAME, [this](){
         // TODO
         // start new session
         // activate new_game_intro_storyboards
      }},
      { EVENT_CONTINUE_A_SAVED_GAME, [this](){
         // TODO
         // Event data: game session id
         // restore session
         // activate gameplay_screen
      }},
      { EVENT_WIN_GAME, [this](){
         // TODO
         // stop session
         // activate game_won_outro_storyboards_screen
      }},
      { EVENT_LOSE_GAME, [this](){
         // TODO
         // stop session
         // activate game_over_screen
      }},
      { EVENT_START_LEVEL, [this](){
         // TODO
         // Event data: level info
         // primary_gameplay_screen-> load level
         // activate primary_gameplay_screen
      }},
      { EVENT_PAUSE_GAME, [this](){
         // TODO
         // guard: not already pause screen
         // pause session?
         // capture "pre-pause screen"
         // activate pause_screen
      }},
      { EVENT_UNPAUSE_GAME, [this](){
         // TODO
         // guard: is paused
         // unpause session?
         // activate "pre-pause screen"
      }},
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
         activate_screen("intro_logos_screen");
      }},
      { EVENT_ACTIVATE_INTRO_STORYBOARDS_SCREEN, [this](){
         activate_screen("intro_storyboards_screen");
      }},
      { EVENT_ACTIVATE_TITLE_SCREEN, [this](){
         activate_screen("title_screen");
      }},
      { EVENT_ACTIVATE_ACHIEVEMENTS_SCREEN, [this](){
         activate_screen("achievements_screen");
      }},
      { EVENT_ACTIVATE_SETTINGS_SCREEN, [this](){
         activate_screen("settings_screen");
      }},
      { EVENT_ACTIVATE_VERSION_SCREEN, [this](){
         activate_screen("version_screen");
      }},
      { EVENT_ACTIVATE_NEW_GAME_INTRO_STORYBOARD_SCREEN, [this](){
         activate_screen("new_game_intro_storyboard");
      }},
      { EVENT_ACTIVATE_LEVEL_SELECT_SCREEN, [this](){
         activate_screen("level_select_screen");
      }},
      { EVENT_ACTIVATE_GAME_OVER_SCREEN, [this](){
         activate_screen("game_over_screen");
      }},
      { EVENT_ACTIVATE_GAME_WON_SCREEN, [this](){
         activate_screen("game_won_screen");
      }},
      { EVENT_ACTIVATE_GAME_WON_OUTRO_STORYBOARD_SCREEN, [this](){
         activate_screen("game_won_outro_storyboard_screen");
      }},
      { EVENT_ACTIVATE_CREDITS_SCREEN, [this](){
         activate_screen("credits_screen");
      }},
      { EVENT_ACTIVATE_PRIMARY_GAMEPLAY_SCREEN, [this](){
         activate_screen("primary_gameplay_screen");
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


