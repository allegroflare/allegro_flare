#pragma once


#include <AllegroFlare/Prototypes/Platforming2D/EntityControlConnectors/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Platforming2D
      {
         namespace EntityControlConnectors
         {
            class Basic2D : public AllegroFlare::Prototypes::Platforming2D::EntityControlConnectors::Base
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/Prototypes/Platforming2D/EntityControlConnectors/Basic2D";

            private:
               std::string property;

            protected:


            public:
               Basic2D(std::string property="[unset-property]");
               ~Basic2D();

               std::string get_property() const;
               bool property_is(std::string possible_type="");
            };
         }
      }
   }
}



