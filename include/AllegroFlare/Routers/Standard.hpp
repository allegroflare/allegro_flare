#pragma once


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

      private:
         enum
         {
            EVENT_UNDEFINED = 0,
            EVENT_INITIALIZE,
            EVENT_EXIT_GAME,
            EVENT_START_NEW_GAME,
            EVENT_CONTINUE_A_SAVED_GAME,
            EVENT_WIN_GAME,
            EVENT_LOSE_GAME,
            EVENT_START_LEVEL,
            EVENT_PAUSE_GAME,
            EVENT_UNPAUSE_GAME,
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
            INTRO_LOGOS_SCREEN,
            INTRO_STORYBOARDS_SCREEN,
            TITLE_SCREEN,
            ACHIEVEMENTS_SCREEN,
            SETTINGS_SCREEN,
            VERSION_SCREEN,
            NEW_GAME_INTRO_STORYBOARD_SCREEN,
            LEVEL_SELECT_SCREEN,
            GAME_OVER_SCREEN,
            GAME_WON_SCREEN,
            GAME_WON_OUTRO_STORYBOARD_SCREEN,
            CREDITS_SCREEN,
            PRIMARY_GAMEPLAY_SCREEN,
         };
         AllegroFlare::GameSession** game_session;

      protected:


      public:
         Standard(AllegroFlare::GameSession** game_session=nullptr);
         virtual ~Standard();

         void set_game_session(AllegroFlare::GameSession** game_session);
         AllegroFlare::GameSession** get_game_session() const;
         virtual void on_route_event(uint32_t route_event=EVENT_UNDEFINED) override;
      };
   }
}



