#pragma once


#include <string>


namespace AllegroFlare
{
   class TimerFormatter
   {
   private:
      int milliseconds;

   public:
      TimerFormatter(int milliseconds);
      ~TimerFormatter();

      std::string format();
   };
}


