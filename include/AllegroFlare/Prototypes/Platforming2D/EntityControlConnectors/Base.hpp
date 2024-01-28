#pragma once


#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Platforming2D
      {
         namespace EntityControlConnectors
         {
            class Base
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/Prototypes/Platforming2D/EntityControlConnectors/Base";

            private:
               std::string type;

            protected:


            public:
               Base(std::string type=AllegroFlare::Prototypes::Platforming2D::EntityControlConnectors::Base::TYPE);
               ~Base();

               std::string get_type() const;
               bool is_type(std::string possible_type="");
            };
         }
      }
   }
}



