#pragma once


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

      std::string generate_now_timestamp_utc();
   };
}



