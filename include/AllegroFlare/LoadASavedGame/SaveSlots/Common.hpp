#pragma once


#include <AllegroFlare/LoadASavedGame/SaveSlots/Base.hpp>
#include <ctime>
#include <string>


namespace AllegroFlare
{
   namespace LoadASavedGame
   {
      namespace SaveSlots
      {
         class Common : public AllegroFlare::LoadASavedGame::SaveSlots::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/LoadASavedGame/SaveSlots/Common";

         private:

         protected:


         public:
            std::string screenshot_of_gameplay_at_save_identifier;
            std::string location_of_save;
            std::string date_and_time_of_save;
            std::string time_since_text;
            std::time_t save_time__seconds_since_epoch;
            Common(std::string screenshot_of_gameplay_at_save_identifier="[unset-screenshot_of_gameplay_at_save_identifier]", std::string location_of_save="[unset-location_of_save]", std::string date_and_time_of_save="[unset-date_and_time_of_save]", std::string time_since_text="[unset-time_since_text]", std::time_t save_time__seconds_since_epoch=0);
            ~Common();

         };
      }
   }
}



