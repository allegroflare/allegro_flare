#pragma once


#include <string>


namespace AllegroFlare
{
   namespace Runners
   {
      class Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/Runners/Base";

      private:
         std::string type;

      protected:


      public:
         Base(std::string type=AllegroFlare::Runners::Base::TYPE);
         ~Base();

         std::string get_type() const;
         bool is_type(std::string possible_type="");
      };
   }
}



