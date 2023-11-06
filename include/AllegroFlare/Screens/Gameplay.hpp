#pragma once


#include <AllegroFlare/Screens/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Screens
   {
      class Gameplay : public AllegroFlare::Screens::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/Screens/Gameplay";

      private:
         std::string property;

      protected:


      public:
         Gameplay(std::string property="[unset-property]");
         ~Gameplay();

         std::string get_property() const;
         bool property_is(std::string possible_type="");
      };
   }
}



