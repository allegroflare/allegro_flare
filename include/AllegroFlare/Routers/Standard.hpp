#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/GameSession.hpp>
#include <AllegroFlare/RouteEventDatas/Base.hpp>
#include <AllegroFlare/Routers/Base.hpp>
#include <AllegroFlare/Routers/Standard.hpp>
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
         static constexpr char* DISPLAY_SETTINGS_SCREEN_IDENTIFIER = (char*)"display_settings_screen";
         static constexpr char* VERSION_SCREEN_IDENTIFIER = (char*)"version_screen";
         static constexpr char* LOAD_A_SAVED_GAME_SCREEN_IDENTIFIER = (char*)"load_a_saved_game_screen";
         static constexpr char* NEW_GAME_INTRO_STORYBOARD_SCREEN_IDENTIFIER = (char*)"new_game_intro_storyboard_screen";
         static constexpr char* LEVEL_SELECT_SCREEN_IDENTIFIER = (char*)"level_select_screen";
         static constexpr char* ARBITRARY_STORYBOARD_SCREEN_IDENTIFIER = (char*)"arbitrary_storyboard_screen";
         static constexpr char* GAME_OVER_SCREEN_IDENTIFIER = (char*)"game_over_screen";
         static constexpr char* GAME_WON_SCREEN_IDENTIFIER = (char*)"game_won_screen";
         static constexpr char* GAME_WON_OUTRO_STORYBOARD_SCREEN_IDENTIFIER = (char*)"game_won_outro_storyboard_screen";
         static constexpr char* CHARACTER_NAME_INPUT_SCREEN_IDENTIFIER = (char*)"character_name_input_screen";
         static constexpr char* CREDITS_SCREEN_IDENTIFIER = (char*)"credits_screen";
         static constexpr char* PRIMARY_GAMEPLAY_SCREEN_IDENTIFIER = (char*)"primary_gameplay_screen";
         static constexpr char* PRIMARY_GAMEPLAY_SUBSCREEN_IDENTIFIER = (char*)"primary_gameplay_subscreen";
         static constexpr char* PAUSE_SCREEN_IDENTIFIER = (char*)"pause_gameplay_screen";
         static constexpr char* TYPE = (char*)"AllegroFlare/Routers/Standard";

      public:

         enum route_event
         {
            EVENT_UNDEFINED = 0,
            EVENT_INITIALIZE,
            EVENT_EXIT_GAME,
            EVENT_START_NEW_GAME,
            EVENT_CONTINUE_FROM_LAST_SAVE,
            EVENT_LOAD_A_SAVED_GAME,
            EVENT_SAVE_GAME,
            EVENT_PAUSE_GAME,
            EVENT_UNPAUSE_GAME,
            EVENT_WIN_GAME,
            EVENT_LOSE_GAME,
            EVENT_START_LEVEL,
            EVENT_EXIT_TO_TITLE_SCREEN,
            EVENT_INTRO_LOGOS_SCREEN_FINISHED,
            EVENT_INTRO_STORYBOARD_SCREEN_FINISHED,
            EVENT_NEW_GAME_INTRO_STORYBOARD_SCREEN_FINISHED,
            EVENT_PRIMARY_GAMEPLAY_SCREEN_FINISHED,
            EVENT_ARBITRARY_STORYBOARD_SCREEN_FINISHED,
            EVENT_GAME_WON_OUTRO_STORYBOARD_SCREEN_FINISHED,
            EVENT_CREDITS_SCREEN_FINISHED,
            EVENT_TITLE_SCREEN_FINISHED,
            EVENT_SUSPEND_ACCUMULATING_PLAYTIME,
            EVENT_START_OR_RESUME_ACCUMULATING_PLAYTIME,
            EVENT_ACTIVATE_INTRO_LOGOS_SCREEN,
            EVENT_ACTIVATE_INTRO_STORYBOARD_SCREEN,
            EVENT_ACTIVATE_TITLE_SCREEN,
            EVENT_ACTIVATE_ACHIEVEMENTS_SCREEN,
            EVENT_ACTIVATE_DISPLAY_SETTINGS_SCREEN,
            EVENT_ACTIVATE_SETTINGS_SCREEN,
            EVENT_ACTIVATE_VERSION_SCREEN,
            EVENT_ACTIVATE_CHARACTER_NAME_INPUT_SCREEN,
            EVENT_ACTIVATE_LOAD_A_SAVED_GAME_SCREEN,
            EVENT_ACTIVATE_NEW_GAME_INTRO_STORYBOARD_SCREEN,
            EVENT_ACTIVATE_LEVEL_SELECT_SCREEN,
            EVENT_ACTIVATE_ARBITRARY_STORYBOARD_SCREEN,
            EVENT_ACTIVATE_GAME_OVER_SCREEN,
            EVENT_ACTIVATE_GAME_WON_SCREEN,
            EVENT_ACTIVATE_GAME_WON_OUTRO_STORYBOARD_SCREEN,
            EVENT_ACTIVATE_CREDITS_SCREEN,
            EVENT_ACTIVATE_PRIMARY_GAMEPLAY_SCREEN,
            EVENT_ACTIVATE_PRIMARY_GAMEPLAY_SUBSCREEN,
            EVENT_ACTIVATE_PAUSE_SCREEN,
            EVENT_ACTIVATE_SCREEN_BY_IDENTIFIER,
            EVENT_LAST_EVENT,
         };
      private:
         AllegroFlare::EventEmitter* event_emitter;
         std::function<bool(AllegroFlare::RouteEventDatas::Base*)> load_level_handler;
         AllegroFlare::GameSession game_session;
         std::function<bool(uint32_t, AllegroFlare::Routers::Standard*, void*)> on_route_event_unhandled_func;
         void* on_route_event_unhandled_func_user_data;
         std::function<void(AllegroFlare::Routers::Standard*, void*)> on_load_last_played_session_or_start_new_func;
         void* on_load_last_played_session_or_start_new_func_user_data;
         std::function<void(AllegroFlare::Routers::Standard*, void*)> on_create_new_session_func;
         void* on_create_new_session_func_user_data;
         std::function<void(AllegroFlare::Routers::Standard*, void*)> on_continue_from_last_save_func;
         void* on_continue_from_last_save_func_user_data;
         std::function<void(AllegroFlare::Routers::Standard*, void*)> on_load_save_file_content_into_gameplay_func;
         void* on_load_save_file_content_into_gameplay_func_user_data;
         std::function<void(AllegroFlare::Routers::Standard*, void*)> on_gameplay_paused_func;
         void* on_gameplay_paused_func_user_data;
         std::function<void(AllegroFlare::Routers::Standard*, void*)> on_gameplay_unpaused_func;
         void* on_gameplay_unpaused_func_user_data;
         std::function<void(AllegroFlare::Routers::Standard*, void*)> on_primary_gameplay_screen_finished_func;
         void* on_primary_gameplay_screen_finished_func_user_data;
         std::function<void(AllegroFlare::Routers::Standard*, void*)> on_arbitrary_storyboard_screen_finished_func;
         void* on_arbitrary_storyboard_screen_finished_func_user_data;
         std::function<void(AllegroFlare::Routers::Standard*, void*)> on_arbitrary_storyboard_screen_activated_func;
         void* on_arbitrary_storyboard_screen_activated_func_user_data;

      protected:


      public:
         Standard(AllegroFlare::EventEmitter* event_emitter=nullptr, std::function<bool(AllegroFlare::RouteEventDatas::Base*)> load_level_handler=0);
         virtual ~Standard();

         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_load_level_handler(std::function<bool(AllegroFlare::RouteEventDatas::Base*)> load_level_handler);
         void set_on_route_event_unhandled_func(std::function<bool(uint32_t, AllegroFlare::Routers::Standard*, void*)> on_route_event_unhandled_func);
         void set_on_route_event_unhandled_func_user_data(void* on_route_event_unhandled_func_user_data);
         void set_on_load_last_played_session_or_start_new_func(std::function<void(AllegroFlare::Routers::Standard*, void*)> on_load_last_played_session_or_start_new_func);
         void set_on_load_last_played_session_or_start_new_func_user_data(void* on_load_last_played_session_or_start_new_func_user_data);
         void set_on_create_new_session_func(std::function<void(AllegroFlare::Routers::Standard*, void*)> on_create_new_session_func);
         void set_on_create_new_session_func_user_data(void* on_create_new_session_func_user_data);
         void set_on_continue_from_last_save_func(std::function<void(AllegroFlare::Routers::Standard*, void*)> on_continue_from_last_save_func);
         void set_on_continue_from_last_save_func_user_data(void* on_continue_from_last_save_func_user_data);
         void set_on_load_save_file_content_into_gameplay_func(std::function<void(AllegroFlare::Routers::Standard*, void*)> on_load_save_file_content_into_gameplay_func);
         void set_on_load_save_file_content_into_gameplay_func_user_data(void* on_load_save_file_content_into_gameplay_func_user_data);
         void set_on_gameplay_paused_func(std::function<void(AllegroFlare::Routers::Standard*, void*)> on_gameplay_paused_func);
         void set_on_gameplay_paused_func_user_data(void* on_gameplay_paused_func_user_data);
         void set_on_gameplay_unpaused_func(std::function<void(AllegroFlare::Routers::Standard*, void*)> on_gameplay_unpaused_func);
         void set_on_gameplay_unpaused_func_user_data(void* on_gameplay_unpaused_func_user_data);
         void set_on_primary_gameplay_screen_finished_func(std::function<void(AllegroFlare::Routers::Standard*, void*)> on_primary_gameplay_screen_finished_func);
         void set_on_primary_gameplay_screen_finished_func_user_data(void* on_primary_gameplay_screen_finished_func_user_data);
         void set_on_arbitrary_storyboard_screen_finished_func(std::function<void(AllegroFlare::Routers::Standard*, void*)> on_arbitrary_storyboard_screen_finished_func);
         void set_on_arbitrary_storyboard_screen_finished_func_user_data(void* on_arbitrary_storyboard_screen_finished_func_user_data);
         void set_on_arbitrary_storyboard_screen_activated_func(std::function<void(AllegroFlare::Routers::Standard*, void*)> on_arbitrary_storyboard_screen_activated_func);
         void set_on_arbitrary_storyboard_screen_activated_func_user_data(void* on_arbitrary_storyboard_screen_activated_func_user_data);
         AllegroFlare::EventEmitter* get_event_emitter() const;
         std::function<bool(AllegroFlare::RouteEventDatas::Base*)> get_load_level_handler() const;
         std::function<bool(uint32_t, AllegroFlare::Routers::Standard*, void*)> get_on_route_event_unhandled_func() const;
         void* get_on_route_event_unhandled_func_user_data() const;
         std::function<void(AllegroFlare::Routers::Standard*, void*)> get_on_load_last_played_session_or_start_new_func() const;
         void* get_on_load_last_played_session_or_start_new_func_user_data() const;
         std::function<void(AllegroFlare::Routers::Standard*, void*)> get_on_create_new_session_func() const;
         void* get_on_create_new_session_func_user_data() const;
         std::function<void(AllegroFlare::Routers::Standard*, void*)> get_on_continue_from_last_save_func() const;
         void* get_on_continue_from_last_save_func_user_data() const;
         std::function<void(AllegroFlare::Routers::Standard*, void*)> get_on_load_save_file_content_into_gameplay_func() const;
         void* get_on_load_save_file_content_into_gameplay_func_user_data() const;
         std::function<void(AllegroFlare::Routers::Standard*, void*)> get_on_gameplay_paused_func() const;
         void* get_on_gameplay_paused_func_user_data() const;
         std::function<void(AllegroFlare::Routers::Standard*, void*)> get_on_gameplay_unpaused_func() const;
         void* get_on_gameplay_unpaused_func_user_data() const;
         std::function<void(AllegroFlare::Routers::Standard*, void*)> get_on_primary_gameplay_screen_finished_func() const;
         void* get_on_primary_gameplay_screen_finished_func_user_data() const;
         std::function<void(AllegroFlare::Routers::Standard*, void*)> get_on_arbitrary_storyboard_screen_finished_func() const;
         void* get_on_arbitrary_storyboard_screen_finished_func_user_data() const;
         std::function<void(AllegroFlare::Routers::Standard*, void*)> get_on_arbitrary_storyboard_screen_activated_func() const;
         void* get_on_arbitrary_storyboard_screen_activated_func_user_data() const;
         AllegroFlare::GameSession &get_game_session_ref();
         void emit_route_event(uint32_t route_event=0, AllegroFlare::RouteEventDatas::Base* route_event_data=nullptr, float time_now=0.0f);
         void suspend_accumulating_playtime();
         void start_or_resume_accumulating_playtime();
         static std::string name_for_route_event(uint32_t route_event=0);
         virtual void on_route_event(uint32_t route_event=EVENT_UNDEFINED, AllegroFlare::RouteEventDatas::Base* route_event_data=nullptr, float time_now=0.0f) override;
      };
   }
}



