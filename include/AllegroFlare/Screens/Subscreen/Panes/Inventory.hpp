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
            class Inventory : public AllegroFlare::Screens::Subscreen::Panes::Base
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/Screens/Subscreen/Panes/Inventory";

            private:
               std::string property;

            protected:


            public:
               Inventory(std::string property="[unset-property]");
               ~Inventory();

               std::string get_property() const;
               bool property_is(std::string possible_type="");
            };
         }
      }
   }
}



