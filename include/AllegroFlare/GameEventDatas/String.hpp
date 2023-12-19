#pragma once


#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace GameEventDatas
   {
      class String : public AllegroFlare::GameEventDatas::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/GameEventDatas/String";

      private:
         std::string string;

      protected:


      public:
         String(std::string string="[unset-string]");
         ~String();

         std::string get_string() const;
      };
   }
}



