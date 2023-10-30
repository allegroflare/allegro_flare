#pragma once


#include <string>


namespace AllegroFlare
{
   namespace Levels
   {
      class Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/Levels/Base";

      private:
         std::string type;

      protected:


      public:
         Base(std::string type=AllegroFlare::Levels::Base::TYPE);
         ~Base();

         std::string get_type() const;
         bool is_type(std::string possible_type="");
      };
   }
}



