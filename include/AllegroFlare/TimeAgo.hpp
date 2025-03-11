#pragma once


#include <ctime>
#include <string>


namespace AllegroFlare
{
   class TimeAgo
   {
   private:

   protected:


   public:
      TimeAgo();
      ~TimeAgo();

      static std::string time_ago(std::tm* past=nullptr, std::tm* current=nullptr);
      static std::tm create_local_time_now();
   };
}



