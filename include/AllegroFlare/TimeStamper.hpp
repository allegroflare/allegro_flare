#pragma once


#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>


namespace AllegroFlare
{
   class TimeStamper
   {
   private:

   protected:


   public:
      TimeStamper();
      ~TimeStamper();

      static std::string generate_now_timestamp_utc();
      static std::string generate_time_now_utc_iso8601();
      static std::time_t generate_time_now_since_epoch();
      static std::string user_friendly_time(std::time_t time_=std::time(nullptr));
   };
}



