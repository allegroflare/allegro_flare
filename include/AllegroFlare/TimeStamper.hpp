#pragma once


#include <ctime>
#include <string>
#include <tuple>


namespace AllegroFlare
{
   class TimeStamper
   {
   private:

   protected:


   public:
      TimeStamper();
      ~TimeStamper();

      std::string generate_now_timestamp_utc();
      static std::string to_iso_8601_time_str(std::tm* time_obj=nullptr);
      static std::tuple<bool, std::tm, int> str_to_iso_8601_time(std::string iso_time="");
      static std::tm create_local_time_now();
   };
}



