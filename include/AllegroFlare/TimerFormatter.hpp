#pragma once


#include <string>


namespace AllegroFlare
{
   class TimerFormatter
   {
   private:
      int milliseconds;

   public:
      TimerFormatter(int milliseconds=0);
      ~TimerFormatter();

      std::string format();
   };
}


