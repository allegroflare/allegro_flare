#pragma once


#include <AllegroFlare/RouteEventDatas/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace RouteEventDatas
   {
      class ActivateScreen : public AllegroFlare::RouteEventDatas::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/RouteEventDatas/ActivateScreen";

      private:
         std::string screen_identifier;

      protected:


      public:
         ActivateScreen(std::string screen_identifier="[unset-screen_identifier]");
         ~ActivateScreen();

         void set_screen_identifier(std::string screen_identifier);
         std::string get_screen_identifier() const;
      };
   }
}



