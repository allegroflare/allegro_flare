#pragma once


#include <AllegroFlare/Screens/Subscreen/Panes/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Screens
   {
      namespace Subscreen
      {
         namespace Panes
         {
            class Airwing : public AllegroFlare::Screens::Subscreen::Panes::Base
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/Screens/Subscreen/Panes/Airwing";

            private:
               std::string property;

            protected:


            public:
               Airwing(std::string property="[unset-property]");
               ~Airwing();

               std::string get_property() const;
               bool property_is(std::string possible_type="");
            };
         }
      }
   }
}



