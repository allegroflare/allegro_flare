#pragma once


#include <ctime>
#include <string>
#include <utility>


namespace AllegroFlare
{
   class TimeAgo
   {
   private:

   protected:


   public:
      TimeAgo();
      ~TimeAgo();

      static std::pair<std::time_t, std::string> time_ago(std::time_t past_time=std::time(0), std::time_t current_time=std::time(0));
      static std::time_t generate_time_now_since_epoch();
      static std::string format(int value=0, std::string unit="[unset-unit]");
   };
}



