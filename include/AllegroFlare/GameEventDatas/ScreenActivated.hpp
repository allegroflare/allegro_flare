#pragma once


#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace GameEventDatas
   {
      class ScreenActivated : public AllegroFlare::GameEventDatas::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/GameEventDatas/ScreenActivated";

      private:
         std::string screen_identifier;

      protected:


      public:
         ScreenActivated(std::string screen_identifier="[unset-screen_identifier]");
         ~ScreenActivated();

         std::string get_screen_identifier() const;
      };
   }
}



