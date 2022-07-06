#pragma once


#include <string>


namespace AllegroFlare
{
   class TimeStamper
   {
   private:

   public:
      TimeStamper();
      ~TimeStamper();

      std::string generate_now_timestamp_utc();
   };
}



