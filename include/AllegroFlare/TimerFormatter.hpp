#pragma once


#include <string>
#include <cstdint>


namespace AllegroFlare
{
   class TimerFormatter
   {
   private:
      int64_t milliseconds;

   public:
      TimerFormatter(int64_t milliseconds=0);
      ~TimerFormatter();

      std::string format();
      std::string format_hms();

      std::string infer_hours_fragment();
      std::string infer_minutes_fragment();
      std::string infer_seconds_fragment();
      std::string infer_milliseconds_fragment();

      bool has_hours();
   };
}


