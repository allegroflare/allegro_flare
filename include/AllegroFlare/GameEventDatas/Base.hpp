#pragma once


#include <string>


namespace AllegroFlare
{
   namespace GameEventDatas
   {
      class Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/GameEventDatas/Base";

      private:
         std::string type;

      protected:


      public:
         Base(std::string type=AllegroFlare::GameEventDatas::Base::TYPE);
         ~Base();

         void set_type(std::string type);
         std::string get_type() const;
         bool is_type(std::string possible_type="");
      };
   }
}



