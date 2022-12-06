#pragma once


#include <AllegroFlare/Prototypes/Platforming2D/Entities/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Platforming2D
      {
         namespace Entities
         {
            class Basic2D : public AllegroFlare::Prototypes::Platforming2D::Entities::Base
            {
            public:
               static constexpr char* TYPE = (char*)"Entities/Basic2D";

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



