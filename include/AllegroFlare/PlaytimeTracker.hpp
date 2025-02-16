#pragma once


#include <AllegroFlare/Timer.hpp>
#include <chrono>
#include <string>


namespace AllegroFlare
{
   class PlaytimeTracker
   {
   private:
      std::chrono::milliseconds previous_accumulated_playtime_msec;
      AllegroFlare::Timer current_playtime_timer;

   protected:


   public:
      PlaytimeTracker();
      ~PlaytimeTracker();

      std::chrono::milliseconds get_previous_accumulated_playtime_msec() const;
      void start();
      void pause();
      void unpause();
      std::chrono::milliseconds calculate_total_playtime();
      std::string formatted_current_total_playtime_hms();
      std::string to_string();
      void from_string(std::string milliseconds_str="0");
      static std::string milliseconds_to_string(std::chrono::milliseconds milliseconds={});
      static std::chrono::milliseconds milliseconds_from_string(std::string milliseconds_str="0");
   };
}



