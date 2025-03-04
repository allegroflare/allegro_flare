#pragma once


#include <AllegroFlare/GameProgressAndStateInfos/Base.hpp>
#include <AllegroFlare/PlaytimeTracker.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   class GameSession
   {
   private:
      float started_at;
      float ended_at;
      bool active;
      AllegroFlare::PlaytimeTracker playtime_tracker;
      AllegroFlare::GameProgressAndStateInfos::Base* game_progress_and_state_info;

   protected:


   public:
      GameSession();
      ~GameSession();

      void set_game_progress_and_state_info(AllegroFlare::GameProgressAndStateInfos::Base* game_progress_and_state_info);
      float get_started_at() const;
      float get_ended_at() const;
      bool get_active() const;
      AllegroFlare::GameProgressAndStateInfos::Base* get_game_progress_and_state_info() const;
      AllegroFlare::PlaytimeTracker &get_playtime_tracker_ref();
      void start_or_resume_playtime_tracking();
      void suspend_playtime_tracking();
      void save();
      void start_session(float started_at=al_get_time());
      void end_session(float ended_at=al_get_time());
      bool is_active();
   };
}



