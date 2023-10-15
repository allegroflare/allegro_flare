#pragma once


#include <string>


namespace AllegroFlare
{
   namespace GameProgressAndStateInfos
   {
      class Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/GameProgressAndStateInfos/Base";

      private:
         std::string type;

      protected:


      public:
         Base(std::string type=AllegroFlare::GameProgressAndStateInfos::Base::TYPE);
         ~Base();

         std::string get_type() const;
         bool is_type(std::string possible_type="");
      };
   }
}



