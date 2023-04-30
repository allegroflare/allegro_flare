#pragma once


#include <allegro5/allegro.h>
#include <set>
#include <string>


namespace AllegroFlare
{
   class GameSession
   {
   private:
      float started_at;
      float ended_at;
      std::set<std::string> level_progress;

   protected:


   public:
      GameSession();
      ~GameSession();

      void set_level_progress(std::set<std::string> level_progress);
      float get_started_at() const;
      float get_ended_at() const;
      std::set<std::string> get_level_progress() const;
      void start_session(float started_at=al_get_time());
      void end_session(float ended_at=al_get_time());
      bool is_active();
      void mark_level_as_finished(std::string level_identifier="[unset-level_identifier]");
      bool is_level_as_finished(std::string level_identifier="[unset-level_identifier]");
   };
}



