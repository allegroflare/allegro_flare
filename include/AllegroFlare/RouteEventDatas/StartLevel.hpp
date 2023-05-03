#pragma once


#include <AllegroFlare/RouteEventDatas/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace RouteEventDatas
   {
      class StartLevel : public AllegroFlare::RouteEventDatas::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/RouteEventDatas/StartLevel";

      private:
         std::string level_identifier;

      protected:


      public:
         StartLevel(std::string level_identifier="[unset-level_identifier]");
         ~StartLevel();

         void set_level_identifier(std::string level_identifier);
         std::string get_level_identifier() const;
      };
   }
}



