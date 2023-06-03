#pragma once


#include <AllegroFlare/RouteEventDatas/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace RouteEventDatas
   {
      class ActivateScreenByIdentifier : public AllegroFlare::RouteEventDatas::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/RouteEventDatas/ActivateScreenByIdentifier";

      private:
         std::string screen_identifier;

      protected:


      public:
         ActivateScreenByIdentifier(std::string screen_identifier="[unset-screen_identifier]");
         ~ActivateScreenByIdentifier();

         void set_screen_identifier(std::string screen_identifier);
         std::string get_screen_identifier() const;
      };
   }
}



