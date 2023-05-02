#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/GameSession.hpp>
#include <AllegroFlare/RouteEventDatas/Base.hpp>
#include <AllegroFlare/Routers/Base.hpp>
#include <cstdint>
#include <functional>
#include <string>


namespace AllegroFlare
{
   namespace Routers
   {
      class Standard : public AllegroFlare::Routers::Base
      {
      public:
         static constexpr char* INTRO_LOGOS_SCREEN_IDENTIFIER = (char*)"intro_logos_screen";
         static constexpr char* INTRO_STORYBOARD_SCREEN_IDENTIFIER = (char*)"intro_storyboards_screen";
         static constexpr char* TITLE_SCREEN_IDENTIFIER = (char*)"title_screen";
         static constexpr char* ACHIEVEMENTS_SCREEN_IDENTIFIER = (char*)"achievements_screen";
         static constexpr char* SETTINGS_SCREEN_IDENTIFIER = (char*)"settings_screen";
         static constexpr char* VERSION_SCREEN_IDENTIFIER = (char*)"version_screen";
         static constexpr char* NEW_GAME_INTRO_STORYBOARD_SCREEN_IDENTIFIER = (char*)"new_game_intro_storyboard_screen";
         static constexpr char* LEVEL_SELECT_SCREEN_IDENTIFIER = (char*)"level_select_screen";
         static constexpr char* GAME_OVER_SCREEN_IDENTIFIER = (char*)"game_over_screen";
         static constexpr char* GAME_WON_SCREEN_IDENTIFIER = (char*)"game_won_screen";
         static constexpr char* GAME_WON_OUTRO_STORYBOARD_SCREEN_IDENTIFIER = (char*)"game_won_outro_storyboard_screen";
         static constexpr char* CREDITS_SCREEN_IDENTIFIER = (char*)"credits_screen";
         static constexpr char* PRIMARY_GAMEPLAY_SCREEN_IDENTIFIER = (char*)"primary_gameplay_screen";
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
            EVENT_INTRO_LOGOS_SCREEN_FINISHED,
            EVENT_INTRO_STORYBOARD_SCREEN_FINISHED,
            EVENT_NEW_GAME_INTRO_STORYBOARD_SCREEN_FINISHED,
            EVENT_PRIMARY_GAMEPLAY_SCREEN_FINISHED,
            EVENT_GAME_WON_OUTRO_STORYBOARD_SCREEN_FINISHED,
            EVENT_CREDITS_SCREEN_FINISHED,
            EVENT_TITLE_SCREEN_FINISHED,
            EVENT_ACTIVATE_INTRO_LOGOS_SCREEN,
            EVENT_ACTIVATE_INTRO_STORYBOARD_SCREEN,
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
         };
      private:
         AllegroFlare::EventEmitter* event_emitter;
         std::function<void(AllegroFlare::RouteEventDatas::Base*)> load_level_handler;
         AllegroFlare::GameSession game_session;

      protected:


      public:
         Standard(AllegroFlare::EventEmitter* event_emitter=nullptr, std::function<void(AllegroFlare::RouteEventDatas::Base*)> load_level_handler=0);
         virtual ~Standard();

         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_load_level_handler(std::function<void(AllegroFlare::RouteEventDatas::Base*)> load_level_handler);
         AllegroFlare::EventEmitter* get_event_emitter() const;
         std::function<void(AllegroFlare::RouteEventDatas::Base*)> get_load_level_handler() const;
         AllegroFlare::GameSession &get_game_session_ref();
         void emit_route_event(uint32_t route_event=0, AllegroFlare::RouteEventDatas::Base* route_event_data=nullptr, float time_now=0.0f);
         static std::string name_for_route_event(uint32_t route_event=0);
         virtual void on_route_event(uint32_t route_event=EVENT_UNDEFINED, AllegroFlare::RouteEventDatas::Base* route_event_data=nullptr, float time_now=0.0f) override;
      };
   }
}



