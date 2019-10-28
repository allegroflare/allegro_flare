

#include <AllegroFlare/TimerFormatter.hpp>

#include <sstream>
#include <iomanip>


namespace AllegroFlare
{
   TimerFormatter::TimerFormatter(int milliseconds)
      : milliseconds(milliseconds)
   {}


   TimerFormatter::~TimerFormatter()
   {
   }


   std::string TimerFormatter::format()
   {
      std::stringstream ss;
      int hours_fragment = milliseconds / 3600000;
      int minutes_fragment = (milliseconds / 60000) % 60;
      int seconds_fragment = (milliseconds / 1000) % 60;
      int milliseconds_fragment = milliseconds % 1000;

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


   std::string TimerFormatter::infer_hours_fragment()
   {
      std::stringstream ss;
      int hours_fragment = milliseconds / 3600000;
      ss << std::setw(2) << std::setfill('0') << hours_fragment;
      return ss.str();
   }


   std::string TimerFormatter::infer_minutes_fragment()
   {
      std::stringstream ss;
      int minutes_fragment = (milliseconds / 60000) % 60;
      ss << std::setw(2) << std::setfill('0') << minutes_fragment;
      return ss.str();
   }


   std::string TimerFormatter::infer_seconds_fragment()
   {
      std::stringstream ss;
      int seconds_fragment = (milliseconds / 1000) % 60;
      ss << std::setw(2) << std::setfill('0') << seconds_fragment;
      return ss.str();
   }


   std::string TimerFormatter::infer_milliseconds_fragment()
   {
      std::stringstream ss;
      int milliseconds_fragment = milliseconds % 1000;
      ss << std::setfill('0') << std::setw(3) << milliseconds_fragment;
      return ss.str();
   }
}


