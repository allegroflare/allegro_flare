#pragma once


#include <string>


namespace AllegroFlare
{
   namespace RouteEventDatas
   {
      class Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/RouteEventDatas/Base";

      private:
         std::string type;

      protected:


      public:
         Base(std::string type=AllegroFlare::RouteEventDatas::Base::TYPE);
         ~Base();

         std::string get_type() const;
         bool is_type(std::string possible_type="");
      };
   }
}



