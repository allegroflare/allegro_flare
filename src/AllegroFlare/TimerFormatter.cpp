

#include <AllegroFlare/TimerFormatter.hpp>

#include <sstream>
#include <iomanip>


namespace AllegroFlare
{
   TimerFormatter::TimerFormatter(int64_t milliseconds)
      : milliseconds(milliseconds)
   {}


   TimerFormatter::~TimerFormatter()
   {
   }


   std::string TimerFormatter::format()
   {
      std::stringstream ss;
      int64_t hours_fragment = milliseconds / 3600000;
      int64_t minutes_fragment = (milliseconds / 60000) % 60;
      int64_t seconds_fragment = (milliseconds / 1000) % 60;
      int64_t milliseconds_fragment = milliseconds % 1000;

      if (hours_fragment > 0) ss << std::setw(2) << std::setfill('0') << hours_fragment << ":";

      ss
         << std::setw(2)
         << std::setfill('0')
         << minutes_fragment
         << ":"
         << std::setw(2)
         << seconds_fragment
         << '.'
         << std::setfill('0')
         << std::setw(3)
         << milliseconds_fragment;

      return ss.str();
   }


   std::string TimerFormatter::format_hms()
   {
      std::stringstream ss;
      int64_t hours_fragment = milliseconds / 3600000;
      int64_t minutes_fragment = (milliseconds / 60000) % 60;
      int64_t seconds_fragment = (milliseconds / 1000) % 60;
      int64_t milliseconds_fragment = milliseconds % 1000;

      bool has_hours = (hours_fragment > 0);
      if (has_hours) ss << std::setw(2) << std::setfill('0') << hours_fragment << "h ";

      ss
         << std::setw(1)
         //<< std::setfill('')
         << minutes_fragment
         << "m "
         << std::setw(1) // TODO: Consider in real-world scenarios if leading 0s are preferred here or not
         << seconds_fragment
         << "s"
         ;
         //<< std::setfill('0')
         //<< std::setw(3)
         //<< milliseconds_fragment;

      return ss.str();
   }


   std::string TimerFormatter::infer_hours_fragment()
   {
      std::stringstream ss;
      int64_t hours_fragment = milliseconds / 3600000;
      ss << std::setw(2) << std::setfill('0') << hours_fragment;
      return ss.str();
   }


   std::string TimerFormatter::infer_minutes_fragment()
   {
      std::stringstream ss;
      int64_t minutes_fragment = (milliseconds / 60000) % 60;
      ss << std::setw(2) << std::setfill('0') << minutes_fragment;
      return ss.str();
   }


   std::string TimerFormatter::infer_seconds_fragment()
   {
      std::stringstream ss;
      int64_t seconds_fragment = (milliseconds / 1000) % 60;
      ss << std::setw(2) << std::setfill('0') << seconds_fragment;
      return ss.str();
   }


   std::string TimerFormatter::infer_milliseconds_fragment()
   {
      std::stringstream ss;
      int64_t milliseconds_fragment = milliseconds % 1000;
      ss << std::setfill('0') << std::setw(3) << milliseconds_fragment;
      return ss.str();
   }


   bool TimerFormatter::has_hours()
   {
      // TODO: Test this
      int64_t hours_fragment = milliseconds / 3600000;
      return hours_fragment > 0;
   }
}


