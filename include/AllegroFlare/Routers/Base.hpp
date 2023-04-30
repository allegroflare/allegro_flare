#pragma once


#include <string>


namespace AllegroFlare
{
   namespace Routers
   {
      class Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/Routers/Base";

      private:
         std::string type;

      protected:


      public:
         Base(std::string type=AllegroFlare::Routers::Base::TYPE);
         ~Base();

         std::string get_type() const;
         bool is_type(std::string possible_type="");
      };
   }
}



