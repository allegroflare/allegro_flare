

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
      int hours_partial = milliseconds / 3600000;
      int minutes_partial = (milliseconds / 60000) % 60;
      int seconds_partial = (milliseconds / 1000) % 60;
      int milliseconds_partial = milliseconds % 1000;

      if (hours_partial > 0) ss << std::setw(2) << std::setfill('0') << hours_partial << ":";

      ss
         << std::setw(2)
         << std::setfill('0')
         << minutes_partial
         << ":"
         << std::setw(2)
         << seconds_partial
         << '.'
         << std::setfill('0')
         << std::setw(3)
         << milliseconds_partial;

      return ss.str();
   }
}


