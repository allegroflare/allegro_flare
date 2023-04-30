#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/GameSession.hpp>
#include <AllegroFlare/Routers/Base.hpp>
#include <cstdint>


namespace AllegroFlare
{
   namespace Routers
   {
      class Standard : public AllegroFlare::Routers::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/Routers/Standard";

      public:

         enum route_event
         {
            EVENT_UNDEFINED = 0,
            EVENT_INITIALIZE,
            EVENT_EXIT_GAME,
            EVENT_START_NEW_GAME,
            EVENT_CONTINUE_A_SAVED_GAME,
            EVENT_WIN_GAME,
            EVENT_LOSE_GAME,
            EVENT_START_LEVEL,
            EVENT_EXIT_TO_TITLE_SCREEN,
            EVENT_INTRO_LOGOS_INISHED,
            EVENT_INTRO_STORYBOARDS_FINISHED,
            EVENT_NEW_GAME_INTRO_STORYBOARDS_FINISHED,
            EVENT_GAME_WON_OUTRO_STORYBOARDS_FINISHED,
            EVENT_CREDITS_SCREEN_FINISHED,
            EVENT_TITLE_SCREEN_TIMEOUT,
            EVENT_ACTIVATE_INTRO_LOGOS_SCREEN,
            EVENT_ACTIVATE_INTRO_STORYBOARDS_SCREEN,
            EVENT_ACTIVATE_TITLE_SCREEN,
            EVENT_ACTIVATE_ACHIEVEMENTS_SCREEN,
            EVENT_ACTIVATE_SETTINGS_SCREEN,
            EVENT_ACTIVATE_VERSION_SCREEN,
            EVENT_ACTIVATE_NEW_GAME_INTRO_STORYBOARD_SCREEN,
            EVENT_ACTIVATE_LEVEL_SELECT_SCREEN,
            EVENT_ACTIVATE_GAME_OVER_SCREEN,
            EVENT_ACTIVATE_GAME_WON_SCREEN,
            EVENT_ACTIVATE_GAME_WON_OUTRO_STORYBOARD_SCREEN,
            EVENT_ACTIVATE_CREDITS_SCREEN,
            EVENT_ACTIVATE_PRIMARY_GAMEPLAY_SCREEN,
            INTRO_LOGOS_SCREEN_IDENTIFIER,
            INTRO_STORYBOARDS_SCREEN_IDENTIFIER,
            TITLE_SCREEN_IDENTIFIER,
            ACHIEVEMENTS_SCREEN_IDENTIFIER,
            SETTINGS_SCREEN_IDENTIFIER,
            VERSION_SCREEN_IDENTIFIER,
            NEW_GAME_INTRO_STORYBOARD_SCREEN_IDENTIFIER,
            LEVEL_SELECT_SCREEN_IDENTIFIER,
            GAME_OVER_SCREEN_IDENTIFIER,
            GAME_WON_SCREEN_IDENTIFIER,
            GAME_WON_OUTRO_STORYBOARD_SCREEN_IDENTIFIER,
            CREDITS_SCREEN_IDENTIFIER,
            PRIMARY_GAMEPLAY_SCREEN_IDENTIFIER,
         };
      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::GameSession game_session;

      protected:


      public:
         Standard(AllegroFlare::EventEmitter* event_emitter=nullptr);
         virtual ~Standard();

         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         AllegroFlare::EventEmitter* get_event_emitter() const;
         AllegroFlare::GameSession &get_game_session_ref();
         void emit_route_event(uint32_t route_event=0);
         virtual void on_route_event(uint32_t route_event=EVENT_UNDEFINED) override;
      };
   }
}



